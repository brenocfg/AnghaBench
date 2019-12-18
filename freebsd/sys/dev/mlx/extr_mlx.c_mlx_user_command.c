#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct mlx_usercommand {int mu_bufptr; int /*<<< orphan*/  mu_datasize; int /*<<< orphan*/  mu_buf; int /*<<< orphan*/  mu_status; int /*<<< orphan*/  mu_command; } ;
struct mlx_softc {int /*<<< orphan*/  mlx_buffer_dmat; } ;
struct mlx_command {int /*<<< orphan*/  mc_status; int /*<<< orphan*/  mc_length; void* mc_data; int /*<<< orphan*/  mc_dmamap; struct mlx_usercommand* mc_private; int /*<<< orphan*/  mc_mailbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MLX_IO_LOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_IO_UNLOCK (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_MAXPHYS ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx_command*,int /*<<< orphan*/ ) ; 
 int copyin (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int copyout (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  debug_called (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 void* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx_command* mlx_alloccmd (struct mlx_softc*) ; 
 scalar_t__ mlx_getslot (struct mlx_command*) ; 
 int /*<<< orphan*/  mlx_releasecmd (struct mlx_command*) ; 
 int /*<<< orphan*/  mlx_user_cb ; 

__attribute__((used)) static int
mlx_user_command(struct mlx_softc *sc, struct mlx_usercommand *mu)
{
    struct mlx_command	*mc;
    void		*kbuf;
    int			error;
    
    debug_called(0);
    
    kbuf = NULL;
    mc = NULL;
    error = ENOMEM;

    /* get ourselves a command and copy in from user space */
    MLX_IO_LOCK(sc);
    if ((mc = mlx_alloccmd(sc)) == NULL) {
	MLX_IO_UNLOCK(sc);
	return(error);
    }
    bcopy(mu->mu_command, mc->mc_mailbox, sizeof(mc->mc_mailbox));
    debug(0, "got command buffer");

    /*
     * if we need a buffer for data transfer, allocate one and copy in its
     * initial contents
     */
    if (mu->mu_datasize > 0) {
	if (mu->mu_datasize > MLX_MAXPHYS) {
	    error = EINVAL;
	    goto out;
	}
	MLX_IO_UNLOCK(sc);
	if (((kbuf = malloc(mu->mu_datasize, M_DEVBUF, M_WAITOK)) == NULL) ||
	    (error = copyin(mu->mu_buf, kbuf, mu->mu_datasize))) {
	    MLX_IO_LOCK(sc);
	    goto out;
	}
	MLX_IO_LOCK(sc);
	debug(0, "got kernel buffer");
    }

    /* get a command slot */
    if (mlx_getslot(mc))
	goto out;
    debug(0, "got a slot");

    if (mu->mu_datasize > 0) {

	/* range check the pointer to physical buffer address */
	if ((mu->mu_bufptr < 0) || (mu->mu_bufptr > (sizeof(mu->mu_command) -
						     sizeof(u_int32_t)))) {
	    error = EINVAL;
	    goto out;
	}
    }

    /* map the command so the controller can see it */
    mc->mc_data = kbuf;
    mc->mc_length = mu->mu_datasize;
    mc->mc_private = mu;
    error = bus_dmamap_load(sc->mlx_buffer_dmat, mc->mc_dmamap, mc->mc_data,
			    mc->mc_length, mlx_user_cb, mc, BUS_DMA_NOWAIT);
    if (error)
	goto out;

    /* copy out status and data */
    mu->mu_status = mc->mc_status;
    if (mu->mu_datasize > 0) {
	MLX_IO_UNLOCK(sc);
	error = copyout(kbuf, mu->mu_buf, mu->mu_datasize);
	MLX_IO_LOCK(sc);
    }

 out:
    mlx_releasecmd(mc);
    MLX_IO_UNLOCK(sc);
    if (kbuf != NULL)
	free(kbuf, M_DEVBUF);
    return(error);
}
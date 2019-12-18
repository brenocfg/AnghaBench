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
struct mlx_softc {int /*<<< orphan*/  mlx_mem; } ;
struct mlx_command {int /*<<< orphan*/ * mc_mailbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 int MLX_V4_GET_IDBR (struct mlx_softc*) ; 
 int MLX_V4_IDB_FULL ; 
 int /*<<< orphan*/  MLX_V4_IDB_HWMBOX_CMD ; 
 int /*<<< orphan*/  MLX_V4_MAILBOX ; 
 int /*<<< orphan*/  MLX_V4_MAILBOX_LENGTH ; 
 int /*<<< orphan*/  MLX_V4_PUT_IDBR (struct mlx_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX_V4_PUT_MAILBOX (struct mlx_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static int
mlx_v4_tryqueue(struct mlx_softc *sc, struct mlx_command *mc)
{
    int		i;
    
    debug_called(2);
    MLX_IO_ASSERT_LOCKED(sc);

    /* ready for our command? */
    if (!(MLX_V4_GET_IDBR(sc) & MLX_V4_IDB_FULL)) {
	/* copy mailbox data to window */
	for (i = 0; i < 13; i++)
	    MLX_V4_PUT_MAILBOX(sc, i, mc->mc_mailbox[i]);
	
	/* memory-mapped controller, so issue a write barrier to ensure the mailbox is filled */
	bus_barrier(sc->mlx_mem, MLX_V4_MAILBOX, MLX_V4_MAILBOX_LENGTH,
			  BUS_SPACE_BARRIER_WRITE);

	/* post command */
	MLX_V4_PUT_IDBR(sc, MLX_V4_IDB_HWMBOX_CMD);
	return(1);
    }
    return(0);
}
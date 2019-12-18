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
struct mlx_softc {int /*<<< orphan*/  mlx_work; } ;
struct mlx_command {scalar_t__ mc_status; int /*<<< orphan*/ * mc_private; int /*<<< orphan*/  (* mc_complete ) (struct mlx_command*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 scalar_t__ MLX_STATUS_BUSY ; 
 struct mlx_command* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct mlx_command* TAILQ_NEXT (struct mlx_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mlx_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  mc_link ; 
 int /*<<< orphan*/  mlx_unmapcmd (struct mlx_command*) ; 
 int /*<<< orphan*/  stub1 (struct mlx_command*) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx_complete(struct mlx_softc *sc) 
{
    struct mlx_command	*mc, *nc;
    
    debug_called(2);
    MLX_IO_ASSERT_LOCKED(sc);

    /* scan the list of busy/done commands */
    mc = TAILQ_FIRST(&sc->mlx_work);
    while (mc != NULL) {
	nc = TAILQ_NEXT(mc, mc_link);

	/* Command has been completed in some fashion */
	if (mc->mc_status != MLX_STATUS_BUSY) {
	
	    /* unmap the command's data buffer */
	    mlx_unmapcmd(mc);
	    /*
	     * Does the command have a completion handler?
	     */
	    if (mc->mc_complete != NULL) {
		/* remove from list and give to handler */
		TAILQ_REMOVE(&sc->mlx_work, mc, mc_link);
		mc->mc_complete(mc);

		/* 
		 * Is there a sleeper waiting on this command?
		 */
	    } else if (mc->mc_private != NULL) {	/* sleeping caller wants to know about it */

		/* remove from list and wake up sleeper */
		TAILQ_REMOVE(&sc->mlx_work, mc, mc_link);
		wakeup_one(mc->mc_private);

		/*
		 * Leave the command for a caller that's polling for it.
		 */
	    } else {
	    }
	}
	mc = nc;
    }
}
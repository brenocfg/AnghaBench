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
struct mly_softc {int dummy; } ;
struct mly_command {void (* mc_complete ) (struct mly_command*) ;int /*<<< orphan*/  mc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLY_CMD_COMPLETE ; 
 int /*<<< orphan*/  debug_called (int) ; 
 struct mly_command* mly_dequeue_complete (struct mly_softc*) ; 
 int /*<<< orphan*/  mly_unmap_command (struct mly_command*) ; 
 int /*<<< orphan*/  wakeup (struct mly_command*) ; 

__attribute__((used)) static void
mly_complete(struct mly_softc *sc)
{
    struct mly_command	*mc;
    void	        (* mc_complete)(struct mly_command *mc);

    debug_called(2);

    /* 
     * Spin pulling commands off the completed queue and processing them.
     */
    while ((mc = mly_dequeue_complete(sc)) != NULL) {

	/*
	 * Free controller resources, mark command complete.
	 *
	 * Note that as soon as we mark the command complete, it may be freed
	 * out from under us, so we need to save the mc_complete field in
	 * order to later avoid dereferencing mc.  (We would not expect to
	 * have a polling/sleeping consumer with mc_complete != NULL).
	 */
	mly_unmap_command(mc);
	mc_complete = mc->mc_complete;
	mc->mc_flags |= MLY_CMD_COMPLETE;

	/* 
	 * Call completion handler or wake up sleeping consumer.
	 */
	if (mc_complete != NULL) {
	    mc_complete(mc);
	} else {
	    wakeup(mc);
	}
    }
    
    /*
     * XXX if we are deferring commands due to controller-busy status, we should
     *     retry submitting them here.
     */
}
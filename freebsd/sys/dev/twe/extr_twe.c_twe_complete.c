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
struct twe_softc {int dummy; } ;
struct twe_request {int tr_flags; int /*<<< orphan*/  (* tr_complete ) (struct twe_request*) ;} ;

/* Variables and functions */
 int TWE_CMD_SLEEPER ; 
 int /*<<< orphan*/  debug (int,char*,...) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  stub1 (struct twe_request*) ; 
 struct twe_request* twe_dequeue_complete (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_unmap_request (struct twe_request*) ; 
 int /*<<< orphan*/  wakeup_one (struct twe_request*) ; 

__attribute__((used)) static void
twe_complete(struct twe_softc *sc) 
{
    struct twe_request	*tr;
    
    debug_called(5);

    /*
     * Pull commands off the completed list, dispatch them appropriately
     */
    while ((tr = twe_dequeue_complete(sc)) != NULL) {
	/* unmap the command's data buffer */
	twe_unmap_request(tr);

	/* dispatch to suit command originator */
	if (tr->tr_complete != NULL) {		/* completion callback */
	    debug(2, "call completion handler %p", tr->tr_complete);
	    tr->tr_complete(tr);

	} else if (tr->tr_flags & TWE_CMD_SLEEPER) {	/* caller is asleep waiting */
	    debug(2, "wake up command owner on %p", tr);
	    wakeup_one(tr);

	} else {					/* caller is polling command */
	    debug(2, "command left for owner");
	}
    }   
}
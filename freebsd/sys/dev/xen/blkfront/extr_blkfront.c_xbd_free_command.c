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
struct xbd_command {int cm_flags; int /*<<< orphan*/  cm_sc; int /*<<< orphan*/ * cm_complete; int /*<<< orphan*/ * cm_bp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int XBDCF_INITIALIZER ; 
 int XBDCF_Q_MASK ; 
 int /*<<< orphan*/  XBDF_CM_SHORTAGE ; 
 int /*<<< orphan*/  XBD_Q_FREE ; 
 int XBD_Q_NONE ; 
 int /*<<< orphan*/  xbd_enqueue_cm (struct xbd_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbd_thaw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xbd_free_command(struct xbd_command *cm)
{

	KASSERT((cm->cm_flags & XBDCF_Q_MASK) == XBD_Q_NONE,
	    ("Freeing command that is still on queue %d.",
	    cm->cm_flags & XBDCF_Q_MASK));

	cm->cm_flags = XBDCF_INITIALIZER;
	cm->cm_bp = NULL;
	cm->cm_complete = NULL;
	xbd_enqueue_cm(cm, XBD_Q_FREE);
	xbd_thaw(cm->cm_sc, XBDF_CM_SHORTAGE);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mpt_softc {int dummy; } ;
typedef  int /*<<< orphan*/  request_t ;
struct TYPE_3__ {int Event; } ;
typedef  TYPE_1__ MSG_EVENT_NOTIFY_REPLY ;

/* Variables and functions */
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
mpt_stdevent(struct mpt_softc *mpt, request_t *req, MSG_EVENT_NOTIFY_REPLY *msg)
{

	mpt_lprt(mpt, MPT_PRT_DEBUG, "mpt_stdevent: 0x%x\n", msg->Event & 0xFF);
	/* Event was not for us. */
	return (0);
}
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
struct mpt_softc {int dummy; } ;
typedef  int /*<<< orphan*/  request_t ;
typedef  int /*<<< orphan*/  MSG_EVENT_NOTIFY_REPLY ;

/* Variables and functions */

__attribute__((used)) static int
mpt_user_event(struct mpt_softc *mpt, request_t *req,
    MSG_EVENT_NOTIFY_REPLY *msg)
{

	/* Someday we may want to let a user daemon listen for events? */
	return (0);
}
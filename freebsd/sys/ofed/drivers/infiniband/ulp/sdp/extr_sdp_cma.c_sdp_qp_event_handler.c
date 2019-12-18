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
struct socket {int dummy; } ;
struct ib_event {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_event_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_dbg (struct socket*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sdp_qp_event_handler(struct ib_event *event, void *data)
{
	struct socket *sk = data;

	sdp_dbg(sk, "QP Event: %s (%d)", ib_event_msg(event->event),
	    event->event);
}
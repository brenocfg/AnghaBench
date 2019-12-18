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
typedef  int /*<<< orphan*/  u_int32 ;
struct req_pkt {int dummy; } ;
struct info_loop {void* watchdog_timer; void* compliance; int /*<<< orphan*/  drift_comp; int /*<<< orphan*/  last_offset; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  l_fp ;
typedef  int /*<<< orphan*/  endpt ;

/* Variables and functions */
 int /*<<< orphan*/  DTOLFP (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTONL_FP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ current_time ; 
 int drift_comp ; 
 int /*<<< orphan*/  flush_pkt () ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int last_offset ; 
 int /*<<< orphan*/  more_pkt () ; 
 scalar_t__ prepare_pkt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct req_pkt*,int) ; 
 scalar_t__ sys_epoch ; 
 scalar_t__ tc_counter ; 

__attribute__((used)) static void
loop_info(
	sockaddr_u *srcadr,
	endpt *inter,
	struct req_pkt *inpkt
	)
{
	struct info_loop *li;
	l_fp ltmp;

	li = (struct info_loop *)prepare_pkt(srcadr, inter, inpkt,
	    sizeof(struct info_loop));

	DTOLFP(last_offset, &ltmp);
	HTONL_FP(&ltmp, &li->last_offset);
	DTOLFP(drift_comp * 1e6, &ltmp);
	HTONL_FP(&ltmp, &li->drift_comp);
	li->compliance = htonl((u_int32)(tc_counter));
	li->watchdog_timer = htonl((u_int32)(current_time - sys_epoch));

	(void) more_pkt();
	flush_pkt();
}
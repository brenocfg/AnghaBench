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
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u_int32 ;
typedef  int /*<<< orphan*/  u_int ;
typedef  scalar_t__ u_char ;
struct req_pkt {int dummy; } ;
struct info_mem_stats {scalar_t__* hashcount; void* demobilizations; void* allocations; void* findpeer_calls; void* freepeermem; void* totalpeermem; void* timereset; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  endpt ;

/* Variables and functions */
 int NTP_HASH_SIZE ; 
 int /*<<< orphan*/  UCHAR_MAX ; 
 scalar_t__ current_time ; 
 scalar_t__ findpeer_calls ; 
 int /*<<< orphan*/  flush_pkt () ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 scalar_t__ max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  more_pkt () ; 
 scalar_t__ peer_allocations ; 
 scalar_t__ peer_demobilizations ; 
 scalar_t__ peer_free_count ; 
 scalar_t__* peer_hash_count ; 
 scalar_t__ peer_timereset ; 
 scalar_t__ prepare_pkt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct req_pkt*,int) ; 
 scalar_t__ total_peer_structs ; 

__attribute__((used)) static void
mem_stats(
	sockaddr_u *srcadr,
	endpt *inter,
	struct req_pkt *inpkt
	)
{
	register struct info_mem_stats *ms;
	register int i;

	ms = (struct info_mem_stats *)prepare_pkt(srcadr, inter, inpkt,
						  sizeof(struct info_mem_stats));

	ms->timereset = htonl((u_int32)(current_time - peer_timereset));
	ms->totalpeermem = htons((u_short)total_peer_structs);
	ms->freepeermem = htons((u_short)peer_free_count);
	ms->findpeer_calls = htonl((u_int32)findpeer_calls);
	ms->allocations = htonl((u_int32)peer_allocations);
	ms->demobilizations = htonl((u_int32)peer_demobilizations);

	for (i = 0; i < NTP_HASH_SIZE; i++)
		ms->hashcount[i] = (u_char)
		    max((u_int)peer_hash_count[i], UCHAR_MAX);

	(void) more_pkt();
	flush_pkt();
}
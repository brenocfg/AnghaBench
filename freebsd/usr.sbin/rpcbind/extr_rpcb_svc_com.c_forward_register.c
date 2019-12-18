#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
typedef  int time_t ;
struct netbuf {int dummy; } ;
typedef  scalar_t__ rpcvers_t ;
typedef  scalar_t__ rpcproc_t ;
struct TYPE_2__ {int time; int flag; scalar_t__ caller_xid; scalar_t__ reply_type; scalar_t__ versnum; int forward_fd; char* uaddr; scalar_t__ forward_xid; int /*<<< orphan*/ * caller_addr; } ;

/* Variables and functions */
 TYPE_1__* FINFO ; 
 int FINFO_ACTIVE ; 
 int MAXTIME_OFF ; 
 int NFORWARD ; 
 int /*<<< orphan*/  free_slot_by_index (int) ; 
 int /*<<< orphan*/  netbufcmp (int /*<<< orphan*/ *,struct netbuf*) ; 
 int /*<<< orphan*/ * netbufdup (struct netbuf*) ; 
 int /*<<< orphan*/  rpcb_rmtcalls ; 
 void* time (int*) ; 

__attribute__((used)) static int
forward_register(u_int32_t caller_xid, struct netbuf *caller_addr,
		 int forward_fd, char *uaddr, rpcproc_t reply_type,
		 rpcvers_t versnum, u_int32_t *callxidp)
{
	int		i;
	int		j = 0;
	time_t		min_time, time_now;
	static u_int32_t	lastxid;
	int		entry = -1;

	min_time = FINFO[0].time;
	time_now = time((time_t *)0);
	/* initialization */
	if (lastxid == 0)
		lastxid = time_now * NFORWARD;

	/*
	 * Check if it is a duplicate entry. Then,
	 * try to find an empty slot.  If not available, then
	 * use the slot with the earliest time.
	 */
	for (i = 0; i < NFORWARD; i++) {
		if (FINFO[i].flag & FINFO_ACTIVE) {
			if ((FINFO[i].caller_xid == caller_xid) &&
			    (FINFO[i].reply_type == reply_type) &&
			    (FINFO[i].versnum == versnum) &&
			    (!netbufcmp(FINFO[i].caller_addr,
					    caller_addr))) {
				FINFO[i].time = time((time_t *)0);
				return (0);	/* Duplicate entry */
			} else {
				/* Should we wait any longer */
				if ((time_now - FINFO[i].time) > MAXTIME_OFF)
					(void) free_slot_by_index(i);
			}
		}
		if (entry == -1) {
			if ((FINFO[i].flag & FINFO_ACTIVE) == 0) {
				entry = i;
			} else if (FINFO[i].time < min_time) {
				j = i;
				min_time = FINFO[i].time;
			}
		}
	}
	if (entry != -1) {
		/* use this empty slot */
		j = entry;
	} else {
		(void) free_slot_by_index(j);
	}
	if ((FINFO[j].caller_addr = netbufdup(caller_addr)) == NULL) {
		return (-1);
	}
	rpcb_rmtcalls++;	/* no of pending calls */
	FINFO[j].flag = FINFO_ACTIVE;
	FINFO[j].reply_type = reply_type;
	FINFO[j].versnum = versnum;
	FINFO[j].time = time_now;
	FINFO[j].caller_xid = caller_xid;
	FINFO[j].forward_fd = forward_fd;
	/*
	 * Though uaddr is not allocated here, it will still be freed
	 * from free_slot_*().
	 */
	FINFO[j].uaddr = uaddr;
	lastxid = lastxid + NFORWARD;
	/* Don't allow a zero xid below. */
	if ((u_int32_t)(lastxid + NFORWARD) <= NFORWARD)
		lastxid = NFORWARD;
	FINFO[j].forward_xid = lastxid + j;	/* encode slot */
	*callxidp = FINFO[j].forward_xid;	/* forward on this xid */
	return (1);
}
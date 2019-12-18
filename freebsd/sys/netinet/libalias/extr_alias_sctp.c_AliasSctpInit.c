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
struct sctpTimerQ {int dummy; } ;
struct sctpNatTableL {int dummy; } ;
struct sctpNatTableG {int dummy; } ;
struct TYPE_2__ {scalar_t__ cur_loc; int /*<<< orphan*/  loc_time; int /*<<< orphan*/ * TimerQ; } ;
struct libalias {int sctpNatTableSize; scalar_t__ sctpLinkCount; TYPE_1__ sctpNatTimer; int /*<<< orphan*/  timeStamp; int /*<<< orphan*/ * sctpTableGlobal; int /*<<< orphan*/ * sctpTableLocal; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SN_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SN_LOG_EVENT ; 
 int SN_TIMER_QUEUE_SIZE ; 
 int /*<<< orphan*/  SctpAliasLog (char*,int) ; 
 void* sn_calloc (int,int) ; 
 int sysctl_hashtable_size ; 
 int /*<<< orphan*/  time_uptime ; 

void AliasSctpInit(struct libalias *la)
{
	/* Initialise association tables*/
	int i;
	la->sctpNatTableSize = sysctl_hashtable_size;
	SN_LOG(SN_LOG_EVENT,
	    SctpAliasLog("Initialising SCTP NAT Instance (hash_table_size:%d)\n", la->sctpNatTableSize));
	la->sctpTableLocal = sn_calloc(la->sctpNatTableSize, sizeof(struct sctpNatTableL));
	la->sctpTableGlobal = sn_calloc(la->sctpNatTableSize, sizeof(struct sctpNatTableG));
	la->sctpNatTimer.TimerQ = sn_calloc(SN_TIMER_QUEUE_SIZE, sizeof(struct sctpTimerQ));
	/* Initialise hash table */
	for (i = 0; i < la->sctpNatTableSize; i++) {
		LIST_INIT(&la->sctpTableLocal[i]);
		LIST_INIT(&la->sctpTableGlobal[i]);
	}

	/* Initialise circular timer Q*/
	for (i = 0; i < SN_TIMER_QUEUE_SIZE; i++)
		LIST_INIT(&la->sctpNatTimer.TimerQ[i]);
#ifdef _KERNEL
	la->sctpNatTimer.loc_time=time_uptime; /* la->timeStamp is not set yet */
#else
	la->sctpNatTimer.loc_time=la->timeStamp;
#endif
	la->sctpNatTimer.cur_loc = 0;
	la->sctpLinkCount = 0;
}
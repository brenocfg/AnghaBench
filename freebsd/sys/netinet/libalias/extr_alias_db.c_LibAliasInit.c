#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {void* tv_sec; } ;
struct TYPE_4__ {void* s_addr; } ;
struct TYPE_3__ {void* s_addr; } ;
struct libalias {int deleteAllLinks; int packetAliasMode; int fireWallFD; scalar_t__ cleanupIndex; scalar_t__ sockCount; scalar_t__ fragmentPtrLinkCount; scalar_t__ fragmentIdLinkCount; scalar_t__ protoLinkCount; scalar_t__ pptpLinkCount; scalar_t__ sctpLinkCount; scalar_t__ tcpLinkCount; scalar_t__ udpLinkCount; scalar_t__ icmpLinkCount; TYPE_2__ targetAddress; TYPE_1__ aliasAddress; int /*<<< orphan*/ * linkTableIn; int /*<<< orphan*/ * linkTableOut; void* lastCleanupTime; void* timeStamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AliasSctpInit (struct libalias*) ; 
 int /*<<< orphan*/  AliasSctpTerm (struct libalias*) ; 
 int /*<<< orphan*/  CleanupAliasData (struct libalias*) ; 
 void* INADDR_ANY ; 
 int /*<<< orphan*/  LIBALIAS_LOCK (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_INIT (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_UNLOCK (struct libalias*) ; 
 int LINK_TABLE_IN_SIZE ; 
 int LINK_TABLE_OUT_SIZE ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct libalias*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LibAliasRefreshModules () ; 
 int /*<<< orphan*/  M_ALIAS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PKT_ALIAS_RESET_ON_ADDR_CHANGE ; 
 int PKT_ALIAS_SAME_PORTS ; 
 int PKT_ALIAS_USE_SOCKETS ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 struct libalias* calloc (int,int) ; 
 int /*<<< orphan*/  finishoff ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  instancehead ; 
 int /*<<< orphan*/  instancelist ; 
 struct libalias* malloc (int,int /*<<< orphan*/ ,int) ; 
 void* time_uptime ; 

struct libalias *
LibAliasInit(struct libalias *la)
{
	int i;
#ifndef	_KERNEL
	struct timeval tv;
#endif

	if (la == NULL) {
#ifdef _KERNEL
#undef malloc	/* XXX: ugly */
		la = malloc(sizeof *la, M_ALIAS, M_WAITOK | M_ZERO);
#else
		la = calloc(sizeof *la, 1);
		if (la == NULL)
			return (la);
#endif

#ifndef	_KERNEL		/* kernel cleans up on module unload */
		if (LIST_EMPTY(&instancehead))
			atexit(finishoff);
#endif
		LIST_INSERT_HEAD(&instancehead, la, instancelist);

#ifdef	_KERNEL
		la->timeStamp = time_uptime;
		la->lastCleanupTime = time_uptime;
#else
		gettimeofday(&tv, NULL);
		la->timeStamp = tv.tv_sec;
		la->lastCleanupTime = tv.tv_sec;
#endif

		for (i = 0; i < LINK_TABLE_OUT_SIZE; i++)
			LIST_INIT(&la->linkTableOut[i]);
		for (i = 0; i < LINK_TABLE_IN_SIZE; i++)
			LIST_INIT(&la->linkTableIn[i]);
#ifdef _KERNEL
		AliasSctpInit(la);
#endif
		LIBALIAS_LOCK_INIT(la);
		LIBALIAS_LOCK(la);
	} else {
		LIBALIAS_LOCK(la);
		la->deleteAllLinks = 1;
		CleanupAliasData(la);
		la->deleteAllLinks = 0;
#ifdef _KERNEL
		AliasSctpTerm(la);
		AliasSctpInit(la);
#endif
	}

	la->aliasAddress.s_addr = INADDR_ANY;
	la->targetAddress.s_addr = INADDR_ANY;

	la->icmpLinkCount = 0;
	la->udpLinkCount = 0;
	la->tcpLinkCount = 0;
	la->sctpLinkCount = 0;
	la->pptpLinkCount = 0;
	la->protoLinkCount = 0;
	la->fragmentIdLinkCount = 0;
	la->fragmentPtrLinkCount = 0;
	la->sockCount = 0;

	la->cleanupIndex = 0;

	la->packetAliasMode = PKT_ALIAS_SAME_PORTS
#ifndef	NO_USE_SOCKETS
	    | PKT_ALIAS_USE_SOCKETS
#endif
	    | PKT_ALIAS_RESET_ON_ADDR_CHANGE;
#ifndef NO_FW_PUNCH
	la->fireWallFD = -1;
#endif
#ifndef _KERNEL
	LibAliasRefreshModules();
#endif
	LIBALIAS_UNLOCK(la);
	return (la);
}
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
struct libalias {int packetAliasMode; int /*<<< orphan*/  logDesc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LIBALIAS_BUF_SIZE ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int PKT_ALIAS_LOG ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
InitPacketAliasLog(struct libalias *la)
{

	LIBALIAS_LOCK_ASSERT(la);
	if (~la->packetAliasMode & PKT_ALIAS_LOG) {
#ifdef _KERNEL
		if ((la->logDesc = malloc(LIBALIAS_BUF_SIZE)))
			;
#else 		
		if ((la->logDesc = fopen("/var/log/alias.log", "w")))
			fprintf(la->logDesc, "PacketAlias/InitPacketAliasLog: Packet alias logging enabled.\n");	       
#endif
		else 
			return (ENOMEM); /* log initialization failed */
		la->packetAliasMode |= PKT_ALIAS_LOG;
	}

	return (1);
}
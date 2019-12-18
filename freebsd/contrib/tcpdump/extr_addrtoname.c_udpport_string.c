#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u_short ;
struct hnamemem {int addr; char const* name; struct hnamemem* nxt; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ndo_error ) (TYPE_1__*,char*) ;} ;
typedef  TYPE_1__ netdissect_options ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int HASHNAMESIZE ; 
 struct hnamemem* newhnamemem (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 char const* strdup (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 
 struct hnamemem* uporttable ; 

const char *
udpport_string(netdissect_options *ndo, register u_short port)
{
	register struct hnamemem *tp;
	register uint32_t i = port;
	char buf[sizeof("00000")];

	for (tp = &uporttable[i & (HASHNAMESIZE-1)]; tp->nxt; tp = tp->nxt)
		if (tp->addr == i)
			return (tp->name);

	tp->addr = i;
	tp->nxt = newhnamemem(ndo);

	(void)snprintf(buf, sizeof(buf), "%u", i);
	tp->name = strdup(buf);
	if (tp->name == NULL)
		(*ndo->ndo_error)(ndo, "udpport_string: strdup(buf)");
	return (tp->name);
}
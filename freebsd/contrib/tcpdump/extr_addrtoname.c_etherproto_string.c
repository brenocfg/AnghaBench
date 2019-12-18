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

/* Variables and functions */
 int HASHNAMESIZE ; 
 int /*<<< orphan*/  NTOHS (int) ; 
 struct hnamemem* eprototable ; 
 void** hex ; 
 struct hnamemem* newhnamemem (TYPE_1__*) ; 
 char const* strdup (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 

const char *
etherproto_string(netdissect_options *ndo, u_short port)
{
	register char *cp;
	register struct hnamemem *tp;
	register uint32_t i = port;
	char buf[sizeof("0000")];

	for (tp = &eprototable[i & (HASHNAMESIZE-1)]; tp->nxt; tp = tp->nxt)
		if (tp->addr == i)
			return (tp->name);

	tp->addr = i;
	tp->nxt = newhnamemem(ndo);

	cp = buf;
	NTOHS(port);
	*cp++ = hex[port >> 12 & 0xf];
	*cp++ = hex[port >> 8 & 0xf];
	*cp++ = hex[port >> 4 & 0xf];
	*cp++ = hex[port & 0xf];
	*cp++ = '\0';
	tp->name = strdup(buf);
	if (tp->name == NULL)
		(*ndo->ndo_error)(ndo, "etherproto_string: strdup(buf)");
	return (tp->name);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct ether_addr {int dummy; } ;
struct enamemem {char const* e_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ndo_error ) (TYPE_1__*,char*) ;int /*<<< orphan*/  ndo_nflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int BUFSIZE ; 
 int EXTRACT_24BITS (int const*) ; 
 scalar_t__ ether_ntohost (char*,struct ether_addr const*) ; 
 void** hex ; 
 struct enamemem* lookup_emem (TYPE_1__*,int const*) ; 
 int /*<<< orphan*/  oui_values ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,char*) ; 
 char* tok2str (int /*<<< orphan*/ ,char*,int) ; 

const char *
etheraddr_string(netdissect_options *ndo, register const u_char *ep)
{
	register int i;
	register char *cp;
	register struct enamemem *tp;
	int oui;
	char buf[BUFSIZE];

	tp = lookup_emem(ndo, ep);
	if (tp->e_name)
		return (tp->e_name);
#ifdef USE_ETHER_NTOHOST
	if (!ndo->ndo_nflag) {
		char buf2[BUFSIZE];

		if (ether_ntohost(buf2, (const struct ether_addr *)ep) == 0) {
			tp->e_name = strdup(buf2);
			if (tp->e_name == NULL)
				(*ndo->ndo_error)(ndo,
						  "etheraddr_string: strdup(buf2)");
			return (tp->e_name);
		}
	}
#endif
	cp = buf;
	oui = EXTRACT_24BITS(ep);
	*cp++ = hex[*ep >> 4 ];
	*cp++ = hex[*ep++ & 0xf];
	for (i = 5; --i >= 0;) {
		*cp++ = ':';
		*cp++ = hex[*ep >> 4 ];
		*cp++ = hex[*ep++ & 0xf];
	}

	if (!ndo->ndo_nflag) {
		snprintf(cp, BUFSIZE - (2 + 5*3), " (oui %s)",
		    tok2str(oui_values, "Unknown", oui));
	} else
		*cp = '\0';
	tp->e_name = strdup(buf);
	if (tp->e_name == NULL)
		(*ndo->ndo_error)(ndo, "etheraddr_string: strdup(buf)");
	return (tp->e_name);
}
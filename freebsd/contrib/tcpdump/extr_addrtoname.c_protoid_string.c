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
typedef  size_t u_int ;
typedef  int u_char ;
struct protoidmem {char const* p_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ndo_error ) (TYPE_1__*,char*) ;} ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 void** hex ; 
 struct protoidmem* lookup_protoid (TYPE_1__*,int const*) ; 
 char const* strdup (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 

const char *
protoid_string(netdissect_options *ndo, register const u_char *pi)
{
	register u_int i, j;
	register char *cp;
	register struct protoidmem *tp;
	char buf[sizeof("00:00:00:00:00")];

	tp = lookup_protoid(ndo, pi);
	if (tp->p_name)
		return tp->p_name;

	cp = buf;
	if ((j = *pi >> 4) != 0)
		*cp++ = hex[j];
	*cp++ = hex[*pi++ & 0xf];
	for (i = 4; (int)--i >= 0;) {
		*cp++ = ':';
		if ((j = *pi >> 4) != 0)
			*cp++ = hex[j];
		*cp++ = hex[*pi++ & 0xf];
	}
	*cp = '\0';
	tp->p_name = strdup(buf);
	if (tp->p_name == NULL)
		(*ndo->ndo_error)(ndo, "protoid_string: strdup(buf)");
	return (tp->p_name);
}
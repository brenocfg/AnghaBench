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
typedef  int u_int ;
typedef  int u_char ;
struct enamemem {char const* e_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ndo_error ) (TYPE_1__*,char*) ;} ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int ISONSAP_MAX_LENGTH ; 
 void** hex ; 
 struct enamemem* lookup_nsap (TYPE_1__*,int const*,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 

const char *
isonsap_string(netdissect_options *ndo, const u_char *nsap,
	       register u_int nsap_length)
{
	register u_int nsap_idx;
	register char *cp;
	register struct enamemem *tp;

	if (nsap_length < 1 || nsap_length > ISONSAP_MAX_LENGTH)
		return ("isonsap_string: illegal length");

	tp = lookup_nsap(ndo, nsap, nsap_length);
	if (tp->e_name)
		return tp->e_name;

	tp->e_name = cp = (char *)malloc(sizeof("xx.xxxx.xxxx.xxxx.xxxx.xxxx.xxxx.xxxx.xxxx.xxxx.xx"));
	if (cp == NULL)
		(*ndo->ndo_error)(ndo, "isonsap_string: malloc");

	for (nsap_idx = 0; nsap_idx < nsap_length; nsap_idx++) {
		*cp++ = hex[*nsap >> 4];
		*cp++ = hex[*nsap++ & 0xf];
		if (((nsap_idx & 1) == 0) &&
		     (nsap_idx + 1 < nsap_length)) {
		     	*cp++ = '.';
		}
	}
	*cp = '\0';
	return (tp->e_name);
}
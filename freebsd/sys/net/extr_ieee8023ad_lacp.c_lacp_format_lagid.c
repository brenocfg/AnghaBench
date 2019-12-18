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
struct lacp_peerinfo {int dummy; } ;
typedef  int /*<<< orphan*/  bstr ;
typedef  int /*<<< orphan*/  astr ;

/* Variables and functions */
 int /*<<< orphan*/  LACP_PARTNERSTR_MAX ; 
 scalar_t__ lacp_compare_peerinfo (struct lacp_peerinfo const*,struct lacp_peerinfo const*) ; 
 char* lacp_format_partner (struct lacp_peerinfo const*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*) ; 

const char *
lacp_format_lagid(const struct lacp_peerinfo *a,
    const struct lacp_peerinfo *b, char *buf, size_t buflen)
{
	char astr[LACP_PARTNERSTR_MAX+1];
	char bstr[LACP_PARTNERSTR_MAX+1];

#if 0
	/*
	 * there's a convention to display small numbered peer
	 * in the left.
	 */

	if (lacp_compare_peerinfo(a, b) > 0) {
		const struct lacp_peerinfo *t;

		t = a;
		a = b;
		b = t;
	}
#endif

	snprintf(buf, buflen, "[%s,%s]",
	    lacp_format_partner(a, astr, sizeof(astr)),
	    lacp_format_partner(b, bstr, sizeof(bstr)));

	return (buf);
}
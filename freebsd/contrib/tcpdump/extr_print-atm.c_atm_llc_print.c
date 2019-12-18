#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {int /*<<< orphan*/  ndo_suppress_default_print; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_DEFAULTPRINT (int /*<<< orphan*/  const*,int) ; 
 int llc_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_int
atm_llc_print(netdissect_options *ndo,
              const u_char *p, int length, int caplen)
{
	int llc_hdrlen;

	llc_hdrlen = llc_print(ndo, p, length, caplen, NULL, NULL);
	if (llc_hdrlen < 0) {
		/* packet not known, print raw packet */
		if (!ndo->ndo_suppress_default_print)
			ND_DEFAULTPRINT(p, caplen);
		llc_hdrlen = -llc_hdrlen;
	}
	return (llc_hdrlen);
}
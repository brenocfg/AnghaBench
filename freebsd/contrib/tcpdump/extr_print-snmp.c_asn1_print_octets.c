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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {scalar_t__ raw; } ;
struct be {int /*<<< orphan*/  asnlen; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static int
asn1_print_octets(netdissect_options *ndo, struct be *elem)
{
	const u_char *p = (const u_char *)elem->data.raw;
	uint32_t asnlen = elem->asnlen;
	uint32_t i;

	ND_TCHECK2(*p, asnlen);
	for (i = asnlen; i-- > 0; p++)
		ND_PRINT((ndo, "_%.2x", *p));
	return 0;

trunc:
	ND_PRINT((ndo, "%s", tstr));
	return -1;
}
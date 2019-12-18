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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {scalar_t__ ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (char const*) ; 
 int lwres_printname (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
lwres_printnamelen(netdissect_options *ndo,
                   const char *p)
{
	uint16_t l;
	int advance;

	if (p + 2 > (const char *)ndo->ndo_snapend)
		goto trunc;
	l = EXTRACT_16BITS(p);
	advance = lwres_printname(ndo, l, p + 2);
	if (advance < 0)
		goto trunc;
	return 2 + advance;

  trunc:
	return -1;
}
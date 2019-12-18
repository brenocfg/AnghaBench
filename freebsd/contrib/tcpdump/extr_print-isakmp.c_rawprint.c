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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,size_t) ; 
 int /*<<< orphan*/  hexprint (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int
rawprint(netdissect_options *ndo, const uint8_t *loc, size_t len)
{
	ND_TCHECK2(*loc, len);

	hexprint(ndo, loc, len);
	return 1;
trunc:
	return 0;
}
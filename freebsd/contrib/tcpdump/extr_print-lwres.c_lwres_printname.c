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
struct TYPE_5__ {scalar_t__ ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  safeputchar (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lwres_printname(netdissect_options *ndo,
                size_t l, const char *p0)
{
	const char *p;
	size_t i;

	p = p0;
	/* + 1 for terminating \0 */
	if (p + l + 1 > (const char *)ndo->ndo_snapend)
		goto trunc;

	ND_PRINT((ndo, " "));
	for (i = 0; i < l; i++)
		safeputchar(ndo, *p++);
	p++;	/* skip terminating \0 */

	return p - p0;

  trunc:
	return -1;
}
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
struct TYPE_5__ {int /*<<< orphan*/  mctx; } ;
typedef  TYPE_1__ isc_radix_tree_t ;
typedef  int /*<<< orphan*/  isc_radix_destroyfunc_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _clear_radix (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void
isc_radix_destroy(isc_radix_tree_t *radix, isc_radix_destroyfunc_t func)
{
	REQUIRE(radix != NULL);
	_clear_radix(radix, func);
	isc_mem_put(radix->mctx, radix, sizeof(*radix));
}
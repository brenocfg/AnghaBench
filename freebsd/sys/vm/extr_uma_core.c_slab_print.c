#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uma_slab_t ;
struct TYPE_3__ {int us_freecount; int /*<<< orphan*/  us_data; int /*<<< orphan*/  us_keg; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
slab_print(uma_slab_t slab)
{
	printf("slab: keg %p, data %p, freecount %d\n",
		slab->us_keg, slab->us_data, slab->us_freecount);
}
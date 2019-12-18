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
typedef  int /*<<< orphan*/  daddr_t ;
typedef  TYPE_1__* blist_t ;
struct TYPE_3__ {int /*<<< orphan*/  bl_avail; } ;

/* Variables and functions */

daddr_t
blist_avail(blist_t bl)
{

	return (bl->bl_avail);
}
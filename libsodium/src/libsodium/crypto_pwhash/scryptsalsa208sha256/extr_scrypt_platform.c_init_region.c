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
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/ * aligned; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ escrypt_region_t ;

/* Variables and functions */

__attribute__((used)) static inline void
init_region(escrypt_region_t *region)
{
    region->base = region->aligned = NULL;
    region->size                   = 0;
}
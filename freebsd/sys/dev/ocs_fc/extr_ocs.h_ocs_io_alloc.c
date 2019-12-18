#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* xport; } ;
typedef  TYPE_2__ ocs_t ;
typedef  int /*<<< orphan*/  ocs_io_t ;
struct TYPE_4__ {int /*<<< orphan*/  io_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ocs_io_pool_io_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ocs_io_t *
ocs_io_alloc(ocs_t *ocs)
{
	return ocs_io_pool_io_alloc(ocs->xport->io_pool);
}
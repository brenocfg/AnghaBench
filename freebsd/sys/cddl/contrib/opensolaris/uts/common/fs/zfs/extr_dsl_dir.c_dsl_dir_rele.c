#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dd_dbuf; TYPE_1__* dd_pool; } ;
typedef  TYPE_2__ dsl_dir_t ;
struct TYPE_5__ {int /*<<< orphan*/  dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dprintf_dd (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ ,void*) ; 

void
dsl_dir_rele(dsl_dir_t *dd, void *tag)
{
	dprintf_dd(dd, "%s\n", "");
	spa_close(dd->dd_pool->dp_spa, tag);
	dmu_buf_rele(dd->dd_dbuf, tag);
}
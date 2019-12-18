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
struct TYPE_5__ {TYPE_1__* ds_dbuf; } ;
typedef  TYPE_2__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dsl_dataset_phys_t ;
struct TYPE_4__ {int /*<<< orphan*/ * db_data; } ;

/* Variables and functions */

inline dsl_dataset_phys_t *
dsl_dataset_phys(dsl_dataset_t *ds)
{
	return (ds->ds_dbuf->db_data);
}
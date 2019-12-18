#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_2__ {int /*<<< orphan*/  ds_guid; } ;

/* Variables and functions */
 TYPE_1__* dsl_dataset_phys (int /*<<< orphan*/ *) ; 

uint64_t
dsl_get_guid(dsl_dataset_t *ds)
{
	return (dsl_dataset_phys(ds)->ds_guid);
}
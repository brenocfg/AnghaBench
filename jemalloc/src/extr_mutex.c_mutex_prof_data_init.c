#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * prev_owner; int /*<<< orphan*/  tot_wait_time; int /*<<< orphan*/  max_wait_time; } ;
typedef  TYPE_1__ mutex_prof_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nstime_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mutex_prof_data_init(mutex_prof_data_t *data) {
	memset(data, 0, sizeof(mutex_prof_data_t));
	nstime_init(&data->max_wait_time, 0);
	nstime_init(&data->tot_wait_time, 0);
	data->prev_owner = NULL;
}
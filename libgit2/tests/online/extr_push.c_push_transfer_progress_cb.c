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
struct TYPE_2__ {scalar_t__ transfer_progress_calls; } ;
typedef  TYPE_1__ record_callbacks_data ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (size_t) ; 

__attribute__((used)) static int push_transfer_progress_cb(
	unsigned int current, unsigned int total, size_t bytes, void* payload)
{
	record_callbacks_data *data = (record_callbacks_data *) payload;
	GIT_UNUSED(current); GIT_UNUSED(total); GIT_UNUSED(bytes);
	if (data->transfer_progress_calls < 0)
		return data->transfer_progress_calls;

	data->transfer_progress_calls++;
	return 0;
}
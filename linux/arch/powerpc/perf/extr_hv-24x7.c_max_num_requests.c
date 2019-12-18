#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hv_24x7_request_buffer {int dummy; } ;

/* Variables and functions */
 int H24x7_DATA_BUFFER_SIZE ; 
 int H24x7_REQUEST_SIZE (int) ; 

__attribute__((used)) static unsigned int max_num_requests(int interface_version)
{
	return (H24x7_DATA_BUFFER_SIZE - sizeof(struct hv_24x7_request_buffer))
		/ H24x7_REQUEST_SIZE(interface_version);
}
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
struct icl_drv_limits {int idl_max_recv_data_segment_length; int idl_max_send_data_segment_length; int idl_max_burst_length; int idl_first_burst_length; } ;

/* Variables and functions */

__attribute__((used)) static int
icl_soft_limits(struct icl_drv_limits *idl)
{

	idl->idl_max_recv_data_segment_length = 128 * 1024;
	idl->idl_max_send_data_segment_length = 128 * 1024;
	idl->idl_max_burst_length = 262144;
	idl->idl_first_burst_length = 65536;

	return (0);
}
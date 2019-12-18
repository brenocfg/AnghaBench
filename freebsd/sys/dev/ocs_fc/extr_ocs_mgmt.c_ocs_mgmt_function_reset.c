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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_device_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_device_detach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
ocs_mgmt_function_reset(ocs_t *ocs, char *name, void *buf, uint32_t buf_len, void *arg_out, uint32_t arg_out_length)
{
	int32_t rc;

	ocs_device_detach(ocs);
	rc = ocs_device_attach(ocs);

	return rc;
}
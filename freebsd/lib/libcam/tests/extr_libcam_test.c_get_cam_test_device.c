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
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 char* atf_tc_get_config_var (int /*<<< orphan*/  const*,char*) ; 

__attribute__((used)) static const char *
get_cam_test_device(const atf_tc_t *tc)
{
	const char *cam_test_device;

	cam_test_device = atf_tc_get_config_var(tc, "cam_test_device");

	return (cam_test_device);
}
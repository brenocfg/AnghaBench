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

/* Variables and functions */
 int /*<<< orphan*/  assert_invalid_config_key_name (char*) ; 

void test_config_validkeyname__accessing_requires_a_valid_name(void)
{
	assert_invalid_config_key_name("");
	assert_invalid_config_key_name(".");
	assert_invalid_config_key_name("..");
	assert_invalid_config_key_name("core.");
	assert_invalid_config_key_name("d#ff.dirstat.lines");
	assert_invalid_config_key_name("diff.dirstat.lines#");
	assert_invalid_config_key_name("dif\nf.dirstat.lines");
	assert_invalid_config_key_name("dif.dir\nstat.lines");
	assert_invalid_config_key_name("dif.dirstat.li\nes");
}
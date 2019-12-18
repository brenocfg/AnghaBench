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
 char* common_test_pidfile_child (char const*,int) ; 

__attribute__((used)) static const char *
test_pidfile_inherited(void)
{
	const char *fn = "test_pidfile_inherited";
	const char *result;

	result = common_test_pidfile_child(fn, 1);
	return (result);
}
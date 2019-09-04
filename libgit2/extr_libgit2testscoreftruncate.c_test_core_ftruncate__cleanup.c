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
 scalar_t__ fd ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  p_close (scalar_t__) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 

void test_core_ftruncate__cleanup(void)
{
	if (fd < 0)
		return;

	p_close(fd);
	fd = 0;

	p_unlink(filename);
}
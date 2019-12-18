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
 int /*<<< orphan*/ * _odb ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 

void test_odb_packed__cleanup(void)
{
	git_odb_free(_odb);
	_odb = NULL;
}
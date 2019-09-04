#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * name; int /*<<< orphan*/  tempfile; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  delete_tempfile (int /*<<< orphan*/ *) ; 
 TYPE_1__* diff_temp ; 
 scalar_t__ is_tempfile_active (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_tempfile(void)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(diff_temp); i++) {
		if (is_tempfile_active(diff_temp[i].tempfile))
			delete_tempfile(&diff_temp[i].tempfile);
		diff_temp[i].name = NULL;
	}
}
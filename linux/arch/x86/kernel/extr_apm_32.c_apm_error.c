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
struct TYPE_2__ {int key; int msg; } ;

/* Variables and functions */
 int ERROR_COUNT ; 
 TYPE_1__* error_table ; 
 int /*<<< orphan*/  pr_notice (char*,char*,int) ; 

__attribute__((used)) static void apm_error(char *str, int err)
{
	int i;

	for (i = 0; i < ERROR_COUNT; i++)
		if (error_table[i].key == err)
			break;
	if (i < ERROR_COUNT)
		pr_notice("%s: %s\n", str, error_table[i].msg);
	else if (err < 0)
		pr_notice("%s: linux error code %i\n", str, err);
	else
		pr_notice("%s: unknown error code %#2.2x\n",
		       str, err);
}
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
struct diff_tempfile {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct diff_tempfile*) ; 
 int /*<<< orphan*/  BUG (char*) ; 
 struct diff_tempfile* diff_temp ; 

__attribute__((used)) static struct diff_tempfile *claim_diff_tempfile(void)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(diff_temp); i++)
		if (!diff_temp[i].name)
			return diff_temp + i;
	BUG("diff is failing to clean up its tempfiles");
}
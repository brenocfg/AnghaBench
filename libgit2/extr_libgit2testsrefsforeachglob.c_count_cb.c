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
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 

__attribute__((used)) static int count_cb(const char *reference_name, void *payload)
{
	int *count = (int *)payload;

	GIT_UNUSED(reference_name);

	(*count)++;

	return 0;
}
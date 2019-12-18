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
 scalar_t__ cur_test_id ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strdup (char const*) ; 
 int /*<<< orphan*/  testnum ; 

void
test_begin(const char *func)
{
    if (cur_test_id)
        free(cur_test_id);
    cur_test_id = strdup(func);
    if (!cur_test_id)
        err(1, "strdup failed");

    printf("\n\nTest %d: %s\n", testnum++, func);
}
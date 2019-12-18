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
typedef  int /*<<< orphan*/  heim_string_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ heim_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heim_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heim_string_create (char const*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
test_string(void)
{
    heim_string_t s1, s2;
    const char *string = "hejsan";

    s1 = heim_string_create(string);
    s2 = heim_string_create(string);

    if (heim_cmp(s1, s2) != 0) {
	printf("the same string is not the same\n");
	exit(1);
    }

    heim_release(s1);
    heim_release(s2);

    return 0;
}
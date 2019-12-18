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
typedef  int /*<<< orphan*/  heim_number_t ;
typedef  int /*<<< orphan*/  heim_auto_release_t ;

/* Variables and functions */
 int /*<<< orphan*/  heim_auto_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heim_auto_release_create () ; 
 int /*<<< orphan*/  heim_number_create (int) ; 
 int /*<<< orphan*/  heim_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heim_string_create (char*) ; 

__attribute__((used)) static int
test_auto_release(void)
{
    heim_auto_release_t ar1, ar2;
    heim_number_t n1;
    heim_string_t s1;

    ar1 = heim_auto_release_create();

    s1 = heim_string_create("hejsan");
    heim_auto_release(s1);

    n1 = heim_number_create(1);
    heim_auto_release(n1);

    ar2 = heim_auto_release_create();

    n1 = heim_number_create(1);
    heim_auto_release(n1);

    heim_release(ar2);
    heim_release(ar1);

    return 0;
}
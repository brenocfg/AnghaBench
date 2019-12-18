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
typedef  int /*<<< orphan*/  heim_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  heim_dict_add_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heim_dict_create (int) ; 
 int /*<<< orphan*/  heim_dict_delete_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heim_number_create (int) ; 
 int /*<<< orphan*/  heim_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heim_string_create (char*) ; 

__attribute__((used)) static int
test_dict(void)
{
    heim_dict_t dict;
    heim_number_t a1 = heim_number_create(1);
    heim_string_t a2 = heim_string_create("hejsan");
    heim_number_t a3 = heim_number_create(3);
    heim_string_t a4 = heim_string_create("foosan");

    dict = heim_dict_create(10);

    heim_dict_add_value(dict, a1, a2);
    heim_dict_add_value(dict, a3, a4);

    heim_dict_delete_key(dict, a3);
    heim_dict_delete_key(dict, a1);

    heim_release(a1);
    heim_release(a2);
    heim_release(a3);
    heim_release(a4);

    heim_release(dict);

    return 0;
}
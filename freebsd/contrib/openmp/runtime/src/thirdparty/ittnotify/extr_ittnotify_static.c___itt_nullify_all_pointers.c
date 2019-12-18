#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* api_list_ptr; } ;
struct TYPE_3__ {int /*<<< orphan*/  null_func; int /*<<< orphan*/ * func_ptr; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 TYPE_2__ _N_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ittapi_global ; 

__attribute__((used)) static void __itt_nullify_all_pointers(void)
{
    int i;
    /* Nulify all pointers except domain_create, string_handle_create  and counter_create */
    for (i = 0; _N_(_ittapi_global).api_list_ptr[i].name != NULL; i++)
        *_N_(_ittapi_global).api_list_ptr[i].func_ptr = _N_(_ittapi_global).api_list_ptr[i].null_func;
}
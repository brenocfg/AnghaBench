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
typedef  scalar_t__ hook_alloc_t ;

/* Variables and functions */
 void* arg_extra ; 
 void* arg_result ; 
 uintptr_t arg_result_raw ; 
 int arg_type ; 
 int /*<<< orphan*/  be_reentrant () ; 
 int /*<<< orphan*/  call_count ; 
 int /*<<< orphan*/  set_args_raw (uintptr_t*,int) ; 

__attribute__((used)) static void
test_alloc_hook(void *extra, hook_alloc_t type, void *result,
    uintptr_t result_raw, uintptr_t args_raw[3]) {
	call_count++;
	arg_extra = extra;
	arg_type = (int)type;
	arg_result = result;
	arg_result_raw = result_raw;
	set_args_raw(args_raw, 3);
	be_reentrant();
}
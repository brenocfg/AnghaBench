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
typedef  void* u_int32_t ;
typedef  void cam_path ;

/* Variables and functions */
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (void*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
hpt_async(void * callback_arg, u_int32_t code, struct cam_path * path,
    void * arg)
{
	/* debug XXXX */
	panic("Here");
	UNREFERENCED_PARAMETER(callback_arg);
	UNREFERENCED_PARAMETER(code);
	UNREFERENCED_PARAMETER(path);
	UNREFERENCED_PARAMETER(arg);

}
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
typedef  int /*<<< orphan*/ * lib_t ;

/* Variables and functions */
 scalar_t__ __itt_get_proc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int __itt_lib_version(lib_t lib)
{
    if (lib == NULL)
        return 0;
    if (__itt_get_proc(lib, "__itt_api_init"))
        return 2;
    if (__itt_get_proc(lib, "__itt_api_version"))
        return 1;
    return 0;
}
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
 int /*<<< orphan*/  _mprotect_readonly ; 
 int _sodium_mprotect (void*,int /*<<< orphan*/ ) ; 

int
sodium_mprotect_readonly(void *ptr)
{
    return _sodium_mprotect(ptr, _mprotect_readonly);
}
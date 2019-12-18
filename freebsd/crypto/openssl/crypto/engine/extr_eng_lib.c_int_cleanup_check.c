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
 scalar_t__ cleanup_stack ; 
 scalar_t__ sk_ENGINE_CLEANUP_ITEM_new_null () ; 

__attribute__((used)) static int int_cleanup_check(int create)
{
    if (cleanup_stack)
        return 1;
    if (!create)
        return 0;
    cleanup_stack = sk_ENGINE_CLEANUP_ITEM_new_null();
    return (cleanup_stack ? 1 : 0);
}
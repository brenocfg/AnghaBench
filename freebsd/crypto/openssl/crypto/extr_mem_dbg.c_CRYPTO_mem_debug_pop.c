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
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_DISABLE ; 
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_ENABLE ; 
 int /*<<< orphan*/  CRYPTO_mem_ctrl (int /*<<< orphan*/ ) ; 
 scalar_t__ mem_check_on () ; 
 int pop_info () ; 

int CRYPTO_mem_debug_pop(void)
{
    int ret = 0;

    if (mem_check_on()) {
        CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_DISABLE);
        ret = pop_info();
        CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ENABLE);
    }
    return ret;
}
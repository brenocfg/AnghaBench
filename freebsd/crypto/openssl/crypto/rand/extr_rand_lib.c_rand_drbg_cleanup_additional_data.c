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
typedef  int /*<<< orphan*/  RAND_POOL ;

/* Variables and functions */
 int /*<<< orphan*/  rand_pool_reattach (int /*<<< orphan*/ *,unsigned char*) ; 

void rand_drbg_cleanup_additional_data(RAND_POOL *pool, unsigned char *out)
{
    rand_pool_reattach(pool, out);
}
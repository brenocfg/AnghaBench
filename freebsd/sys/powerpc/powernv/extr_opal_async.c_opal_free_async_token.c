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
 int /*<<< orphan*/  async_token_pool ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,int,int) ; 

void
opal_free_async_token(int token)
{

	vmem_free(async_token_pool, token, 1);
}
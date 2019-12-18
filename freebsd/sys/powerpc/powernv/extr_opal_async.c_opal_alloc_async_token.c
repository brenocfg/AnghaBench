#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vmem_addr_t ;
struct TYPE_2__ {int completed; } ;

/* Variables and functions */
 int M_FIRSTFIT ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  async_token_pool ; 
 TYPE_1__* completions ; 
 int /*<<< orphan*/  vmem_alloc (int /*<<< orphan*/ ,int,int,size_t*) ; 

int
opal_alloc_async_token(void)
{
	vmem_addr_t token;

	vmem_alloc(async_token_pool, 1, M_FIRSTFIT | M_WAITOK, &token);
	completions[token].completed = false;

	return (token);
}
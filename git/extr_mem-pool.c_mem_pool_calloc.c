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
struct mem_pool {int dummy; } ;

/* Variables and functions */
 void* mem_pool_alloc (struct mem_pool*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 size_t st_mult (size_t,size_t) ; 

void *mem_pool_calloc(struct mem_pool *mem_pool, size_t count, size_t size)
{
	size_t len = st_mult(count, size);
	void *r = mem_pool_alloc(mem_pool, len);
	memset(r, 0, len);
	return r;
}
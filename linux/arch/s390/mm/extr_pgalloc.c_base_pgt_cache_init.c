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
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long _PAGE_TABLE_SIZE ; 
 scalar_t__ base_pgt_cache ; 
 scalar_t__ kmem_cache_create (char*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int base_pgt_cache_init(void)
{
	static DEFINE_MUTEX(base_pgt_cache_mutex);
	unsigned long sz = _PAGE_TABLE_SIZE;

	if (base_pgt_cache)
		return 0;
	mutex_lock(&base_pgt_cache_mutex);
	if (!base_pgt_cache)
		base_pgt_cache = kmem_cache_create("base_pgt", sz, sz, 0, NULL);
	mutex_unlock(&base_pgt_cache_mutex);
	return base_pgt_cache ? 0 : -ENOMEM;
}
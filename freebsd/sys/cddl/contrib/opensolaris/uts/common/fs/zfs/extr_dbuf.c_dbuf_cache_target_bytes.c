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
 unsigned long MIN (int /*<<< orphan*/ ,int) ; 
 int arc_max_bytes () ; 
 int /*<<< orphan*/  dbuf_cache_max_bytes ; 
 int dbuf_cache_shift ; 

__attribute__((used)) static inline unsigned long
dbuf_cache_target_bytes(void)
{
	return MIN(dbuf_cache_max_bytes,
	    arc_max_bytes() >> dbuf_cache_shift);
}
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
typedef  int /*<<< orphan*/  cache ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  destroy_cache (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
destroy_cache_(cache the_cache)
{
	TRACE_IN(destroy_cache_);
	destroy_cache(the_cache);
	TRACE_OUT(destroy_cache_);
}
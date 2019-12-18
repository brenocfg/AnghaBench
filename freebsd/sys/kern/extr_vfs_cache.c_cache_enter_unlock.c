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
struct celockstate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_unlock_buckets_cel (struct celockstate*) ; 
 int /*<<< orphan*/  cache_unlock_vnodes_cel (struct celockstate*) ; 

__attribute__((used)) static void
cache_enter_unlock(struct celockstate *cel)
{

	cache_unlock_buckets_cel(cel);
	cache_unlock_vnodes_cel(cel);
}
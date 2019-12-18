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
struct ptunit_result {int dummy; } ;
struct pt_block_cache {int dummy; } ;
struct pt_bcache_entry {int dummy; } ;

/* Variables and functions */
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_le (int,int) ; 

__attribute__((used)) static struct ptunit_result bcache_size(void)
{
	ptu_uint_le(sizeof(struct pt_block_cache),
		    2 * sizeof(struct pt_bcache_entry));

	return ptu_passed();
}
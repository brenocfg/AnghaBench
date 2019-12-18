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
 int /*<<< orphan*/  Hash_InitTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_count ; 
 int /*<<< orphan*/ * fn_head ; 
 int /*<<< orphan*/  fn_head_s ; 
 int /*<<< orphan*/ * provide_hash ; 
 int /*<<< orphan*/  provide_hash_s ; 

__attribute__((used)) static void
initialize(void)
{

	fn_head = &fn_head_s;

	provide_hash = &provide_hash_s;
	Hash_InitTable(provide_hash, file_count);
}
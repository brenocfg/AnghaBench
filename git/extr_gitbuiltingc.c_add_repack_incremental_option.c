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
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  repack ; 

__attribute__((used)) static void add_repack_incremental_option(void)
{
	argv_array_push(&repack, "--no-write-bitmap-index");
}
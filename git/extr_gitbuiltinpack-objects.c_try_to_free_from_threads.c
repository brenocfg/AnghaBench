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
 int /*<<< orphan*/  packing_data_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packing_data_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_pack_memory (size_t) ; 
 int /*<<< orphan*/  to_pack ; 

__attribute__((used)) static void try_to_free_from_threads(size_t size)
{
	packing_data_lock(&to_pack);
	release_pack_memory(size);
	packing_data_unlock(&to_pack);
}
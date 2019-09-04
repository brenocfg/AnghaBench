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
 size_t pack_mapped ; 
 scalar_t__ unuse_one_window (int /*<<< orphan*/ *) ; 

void release_pack_memory(size_t need)
{
	size_t cur = pack_mapped;
	while (need >= (cur - pack_mapped) && unuse_one_window(NULL))
		; /* nothing */
}
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
struct memory_block {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct memory_block*) ; 
 struct memory_block* to_memory_block (struct device*) ; 

__attribute__((used)) static void memory_block_release(struct device *dev)
{
	struct memory_block *mem = to_memory_block(dev);

	kfree(mem);
}
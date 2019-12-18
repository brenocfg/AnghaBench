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
typedef  size_t uint64_t ;
struct trapframe {size_t tf_level; } ;

/* Variables and functions */
 int MAX_STRAY_LOG ; 
 int* pil_stray_count ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
intr_stray_level(struct trapframe *tf)
{
	uint64_t level;

	level = tf->tf_level;
	if (pil_stray_count[level] < MAX_STRAY_LOG) {
		printf("stray level interrupt %ld\n", level);
		pil_stray_count[level]++;
		if (pil_stray_count[level] >= MAX_STRAY_LOG)
			printf("got %d stray level interrupt %ld's: not "
			    "logging anymore\n", MAX_STRAY_LOG, level);
	}
}
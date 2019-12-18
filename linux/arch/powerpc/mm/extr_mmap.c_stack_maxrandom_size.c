#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int PF_RANDOMIZE ; 
 TYPE_1__* current ; 
 scalar_t__ is_32bit_task () ; 

__attribute__((used)) static inline unsigned long stack_maxrandom_size(void)
{
	if (!(current->flags & PF_RANDOMIZE))
		return 0;

	/* 8MB for 32bit, 1GB for 64bit */
	if (is_32bit_task())
		return (1<<23);
	else
		return (1<<30);
}
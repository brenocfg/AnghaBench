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
struct TYPE_2__ {scalar_t__ td_critnest; } ;

/* Variables and functions */
 TYPE_1__* curthread ; 
 int suword (void volatile*,long) ; 

__attribute__((used)) static int
vm86_suword(volatile void *base, long word)
{

	if (curthread->td_critnest != 0) {
		*(volatile long *)base = word;
		return (0);
	}
	return (suword(base, word));
}
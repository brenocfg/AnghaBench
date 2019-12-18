#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int* __bits; } ;
typedef  TYPE_1__ sigset_t ;

/* Variables and functions */
 int _SIG_WORDS ; 

int
sigfillset(sigset_t *set)
{
	int i;

	for (i = 0; i < _SIG_WORDS; i++)
		set->__bits[i] = ~0U;
	return (0);
}
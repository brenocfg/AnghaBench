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
struct TYPE_3__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ kstring_t ;

/* Variables and functions */
 int ksplit_core (int /*<<< orphan*/ ,int,int*,int**) ; 

__attribute__((used)) static inline int *ksplit(kstring_t *s, int delimiter, int *n)
{
	int max = 0, *offsets = 0;
	*n = ksplit_core(s->s, delimiter, &max, &offsets);
	return offsets;
}
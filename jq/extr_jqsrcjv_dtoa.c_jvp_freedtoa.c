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
struct dtoa_context {int dummy; } ;
struct TYPE_3__ {int maxwds; int k; } ;
typedef  TYPE_1__ Bigint ;

/* Variables and functions */
 int /*<<< orphan*/  Bfree (struct dtoa_context*,TYPE_1__*) ; 

void
jvp_freedtoa(struct dtoa_context* C, char *s)
{
	Bigint *b = (Bigint *)((int *)s - 1);
	b->maxwds = 1 << (b->k = *(int*)b);
	Bfree(C, b);
	}
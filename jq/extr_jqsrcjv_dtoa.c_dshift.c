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
struct TYPE_3__ {int wds; int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ Bigint ;

/* Variables and functions */
 int hi0bits (struct dtoa_context*,int /*<<< orphan*/ ) ; 
 int kmask ; 

__attribute__((used)) static int
dshift(struct dtoa_context* C, Bigint *b, int p2)
{
	int rv = hi0bits(C, b->x[b->wds-1]) - 4;
	if (p2 > 0)
		rv -= p2;
	return rv & kmask;
	}
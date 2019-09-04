#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dtoa_context {int dummy; } ;
struct TYPE_4__ {int* x; int wds; } ;
typedef  TYPE_1__ Bigint ;

/* Variables and functions */
 TYPE_1__* Balloc (struct dtoa_context*,int) ; 

__attribute__((used)) static Bigint *
i2b
 (struct dtoa_context* C, int i)
{
	Bigint *b;

	b = Balloc(C, 1);
	b->x[0] = i;
	b->wds = 1;
	return b;
	}
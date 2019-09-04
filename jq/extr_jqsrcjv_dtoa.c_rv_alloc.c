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
struct dtoa_context {int dummy; } ;
typedef  int /*<<< orphan*/  ULong ;
typedef  int /*<<< orphan*/  Bigint ;

/* Variables and functions */
 scalar_t__ Balloc (struct dtoa_context*,int) ; 

__attribute__((used)) static char *
rv_alloc(struct dtoa_context* C, int i)
{
	int j, k, *r;

	j = sizeof(ULong);
	for(k = 0;
            (int)(sizeof(Bigint) - sizeof(ULong) - sizeof(int)) + j <= i;
		j <<= 1)
			k++;
	r = (int*)Balloc(C, k);
	*r = k;
	return
		(char *)(r+1);
	}
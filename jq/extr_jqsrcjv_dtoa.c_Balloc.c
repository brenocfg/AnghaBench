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
struct dtoa_context {TYPE_1__** freelist; } ;
typedef  int /*<<< orphan*/  ULong ;
struct TYPE_3__ {int k; int maxwds; scalar_t__ wds; scalar_t__ sign; struct TYPE_3__* next; } ;
typedef  TYPE_1__ Bigint ;

/* Variables and functions */
 int Kmax ; 
 scalar_t__ MALLOC (int) ; 

__attribute__((used)) static Bigint *
 Balloc(struct dtoa_context* C, int k)
{
	int x;
	Bigint *rv;

	/* The k > Kmax case does not need ACQUIRE_DTOA_LOCK(0), */
	/* but this case seems very unlikely. */
	if (k <= Kmax && (rv = C->freelist[k]))
		C->freelist[k] = rv->next;
	else {
		x = 1 << k;
		rv = (Bigint *)MALLOC(sizeof(Bigint) + (x-1)*sizeof(ULong));
		rv->k = k;
		rv->maxwds = x;
		}
	rv->sign = rv->wds = 0;
	return rv;
	}
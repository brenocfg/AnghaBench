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
struct TYPE_4__ {long* values; int ncases; } ;
typedef  TYPE_1__* Swtch ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC ; 
 scalar_t__ den (int,int) ; 
 scalar_t__ density ; 
 int* newarray (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swcode (TYPE_1__*,int*,int /*<<< orphan*/ ,int) ; 

void swgen(Swtch swp) {
	int *buckets, k, n;
	long *v = swp->values;

	buckets = newarray(swp->ncases + 1,
		sizeof *buckets, FUNC);
	for (n = k = 0; k < swp->ncases; k++, n++) {
		buckets[n] = k;
		while (n > 0 && den(n-1, k) >= density)
			n--;
	}
	buckets[n] = swp->ncases;
	swcode(swp, buckets, 0, n - 1);
}
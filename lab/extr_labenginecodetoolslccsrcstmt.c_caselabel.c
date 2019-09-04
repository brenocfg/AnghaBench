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
struct TYPE_3__ {int ncases; int size; long* values; int /*<<< orphan*/ * labels; } ;
typedef  int /*<<< orphan*/  Symbol ;
typedef  TYPE_1__* Swtch ;

/* Variables and functions */
 int Aflag ; 
 int /*<<< orphan*/  FUNC ; 
 int /*<<< orphan*/  error (char*,long) ; 
 int /*<<< orphan*/  findlabel (int) ; 
 void* newarray (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void caselabel(Swtch swp, long val, int lab) {
	int k;

	if (swp->ncases >= swp->size)
		{
		long   *vals = swp->values;
		Symbol *labs = swp->labels;
		swp->size *= 2;
		swp->values = newarray(swp->size, sizeof *swp->values, FUNC);
		swp->labels = newarray(swp->size, sizeof *swp->labels, FUNC);
		for (k = 0; k < swp->ncases; k++) {
			swp->values[k] = vals[k];
			swp->labels[k] = labs[k];
		}
		}
	k = swp->ncases;
	for ( ; k > 0 && swp->values[k-1] >= val; k--) {
		swp->values[k] = swp->values[k-1];
		swp->labels[k] = swp->labels[k-1];
	}
	if (k < swp->ncases && swp->values[k] == val)
		error("duplicate case label `%d'\n", val);
	swp->values[k] = val;
	swp->labels[k] = findlabel(lab);
	++swp->ncases;
	if (Aflag >= 2 && swp->ncases == 258)
		warning("more than 257 cases in a switch\n");
}
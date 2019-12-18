#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_6__ {int pri; } ;
typedef  TYPE_1__ collpri_t ;
struct TYPE_9__ {int /*<<< orphan*/  wc; int /*<<< orphan*/ * ref; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ref; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
 int NUM_WT ; 
 int /*<<< orphan*/  REFER ; 
 int /*<<< orphan*/  RESOLVED ; 
#define  T_CHAR 132 
#define  T_COLLELEM 131 
#define  T_ELLIPSIS 130 
#define  T_SYMBOL 129 
#define  T_UNDEFINED 128 
 TYPE_5__* currchar ; 
 TYPE_4__* currelem ; 
 int currorder ; 
 TYPE_3__* currundef ; 
 int /*<<< orphan*/  ellipsis_start ; 
 int* ellipsis_weights ; 
 TYPE_1__* get_pri (int) ; 
 int nextpri ; 
 int* order_weights ; 
 int /*<<< orphan*/ * pri_undefined ; 
 int /*<<< orphan*/  set_pri (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
end_order(void)
{
	int		i;
	int32_t		pri;
	int32_t		ref;
	collpri_t	*p;

	/* advance the priority/weight */
	pri = nextpri;

	switch (currorder) {
	case T_CHAR:
		for (i = 0; i < NUM_WT; i++) {
			if (((ref = order_weights[i]) < 0) ||
			    ((p = get_pri(ref)) == NULL) ||
			    (p->pri == -1)) {
				/* unspecified weight is a self reference */
				set_pri(currchar->ref[i], pri, RESOLVED);
			} else {
				set_pri(currchar->ref[i], ref, REFER);
			}
			order_weights[i] = -1;
		}

		/* leave a cookie trail in case next symbol is ellipsis */
		ellipsis_start = currchar->wc + 1;
		currchar = NULL;
		break;

	case T_ELLIPSIS:
		/* save off the weights were we can find them */
		for (i = 0; i < NUM_WT; i++) {
			ellipsis_weights[i] = order_weights[i];
			order_weights[i] = -1;
		}
		break;

	case T_COLLELEM:
		if (currelem == NULL) {
			INTERR;
		} else {
			for (i = 0; i < NUM_WT; i++) {

				if (((ref = order_weights[i]) < 0) ||
				    ((p = get_pri(ref)) == NULL) ||
				    (p->pri == -1)) {
					set_pri(currelem->ref[i], pri,
					    RESOLVED);
				} else {
					set_pri(currelem->ref[i], ref, REFER);
				}
				order_weights[i] = -1;
			}
		}
		break;

	case T_UNDEFINED:
		for (i = 0; i < NUM_WT; i++) {
			if (((ref = order_weights[i]) < 0) ||
			    ((p = get_pri(ref)) == NULL) ||
			    (p->pri == -1)) {
				set_pri(pri_undefined[i], -1, RESOLVED);
			} else {
				set_pri(pri_undefined[i], ref, REFER);
			}
			order_weights[i] = -1;
		}
		break;

	case T_SYMBOL:
		for (i = 0; i < NUM_WT; i++) {
			if (((ref = order_weights[i]) < 0) ||
			    ((p = get_pri(ref)) == NULL) ||
			    (p->pri == -1)) {
				set_pri(currundef->ref[i], pri, RESOLVED);
			} else {
				set_pri(currundef->ref[i], ref, REFER);
			}
			order_weights[i] = -1;
		}
		break;

	default:
		INTERR;
	}

	nextpri++;
}
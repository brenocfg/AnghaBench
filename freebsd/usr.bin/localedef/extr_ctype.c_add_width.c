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
struct TYPE_3__ {int /*<<< orphan*/  ctype; } ;
typedef  TYPE_1__ ctype_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
 int /*<<< orphan*/  _CTYPE_SW0 ; 
 int /*<<< orphan*/  _CTYPE_SW1 ; 
 int /*<<< orphan*/  _CTYPE_SW2 ; 
 int /*<<< orphan*/  _CTYPE_SW3 ; 
 int /*<<< orphan*/  _CTYPE_SWM ; 
 TYPE_1__* get_ctype (int) ; 

void
add_width(int wc, int width)
{
	ctype_node_t	*ctn;

	if ((ctn = get_ctype(wc)) == NULL) {
		INTERR;
		return;
	}
	ctn->ctype &= ~(_CTYPE_SWM);
	switch (width) {
	case 0:
		ctn->ctype |= _CTYPE_SW0;
		break;
	case 1:
		ctn->ctype |= _CTYPE_SW1;
		break;
	case 2:
		ctn->ctype |= _CTYPE_SW2;
		break;
	case 3:
		ctn->ctype |= _CTYPE_SW3;
		break;
	}
}
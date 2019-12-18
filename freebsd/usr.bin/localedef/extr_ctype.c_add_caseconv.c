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
struct TYPE_3__ {int toupper; int tolower; } ;
typedef  TYPE_1__ ctype_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
#define  T_TOLOWER 129 
#define  T_TOUPPER 128 
 TYPE_1__* get_ctype (int) ; 
 int last_kw ; 

void
add_caseconv(int val, int wc)
{
	ctype_node_t	*ctn;

	ctn = get_ctype(val);
	if (ctn == NULL) {
		INTERR;
		return;
	}

	switch (last_kw) {
	case T_TOUPPER:
		ctn->toupper = wc;
		break;
	case T_TOLOWER:
		ctn->tolower = wc;
		break;
	default:
		INTERR;
		break;
	}
}
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
struct TYPE_4__ {int /*<<< orphan*/  wc; } ;
typedef  TYPE_1__ ctype_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
 int /*<<< orphan*/  add_ctype_impl (TYPE_1__*) ; 
 TYPE_1__* get_ctype (int) ; 
 int /*<<< orphan*/  last_ctype ; 

void
add_ctype(int val)
{
	ctype_node_t	*ctn;

	if ((ctn = get_ctype(val)) == NULL) {
		INTERR;
		return;
	}
	add_ctype_impl(ctn);
	last_ctype = ctn->wc;
}
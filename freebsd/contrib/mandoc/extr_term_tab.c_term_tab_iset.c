#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ n; scalar_t__ s; size_t* t; } ;
struct TYPE_4__ {TYPE_1__ a; } ;

/* Variables and functions */
 size_t* mandoc_reallocarray (size_t*,scalar_t__,int) ; 
 TYPE_2__ tabs ; 

void
term_tab_iset(size_t inc)
{
	if (tabs.a.n >= tabs.a.s) {
		tabs.a.s += 8;
		tabs.a.t = mandoc_reallocarray(tabs.a.t, tabs.a.s,
		    sizeof(*tabs.a.t));
	}
	tabs.a.t[tabs.a.n++] = inc;
}
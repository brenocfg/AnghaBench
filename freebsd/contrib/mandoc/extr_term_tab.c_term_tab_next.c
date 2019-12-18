#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t n; size_t s; size_t* t; } ;
struct TYPE_4__ {size_t n; size_t* t; } ;
struct TYPE_6__ {TYPE_2__ a; TYPE_1__ p; } ;

/* Variables and functions */
 size_t* mandoc_reallocarray (size_t*,size_t,int) ; 
 TYPE_3__ tabs ; 

size_t
term_tab_next(size_t prev)
{
	size_t	 i, j;

	for (i = 0;; i++) {
		if (i == tabs.a.n) {
			if (tabs.p.n == 0)
				return prev;
			tabs.a.n += tabs.p.n;
			if (tabs.a.s < tabs.a.n) {
				tabs.a.s = tabs.a.n;
				tabs.a.t = mandoc_reallocarray(tabs.a.t,
				    tabs.a.s, sizeof(*tabs.a.t));
			}
			for (j = 0; j < tabs.p.n; j++)
				tabs.a.t[i + j] = tabs.p.t[j] +
				    (i ? tabs.a.t[i - 1] : 0);
		}
		if (prev < tabs.a.t[i])
			return tabs.a.t[i];
	}
}
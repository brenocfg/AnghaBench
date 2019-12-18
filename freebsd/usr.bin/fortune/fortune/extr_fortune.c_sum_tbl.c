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
struct TYPE_4__ {scalar_t__ str_longlen; scalar_t__ str_shortlen; scalar_t__ str_numstr; } ;
typedef  TYPE_1__ STRFILE ;

/* Variables and functions */

__attribute__((used)) static void
sum_tbl(STRFILE *t1, STRFILE *t2)
{
	t1->str_numstr += t2->str_numstr;
	if (t1->str_longlen < t2->str_longlen)
		t1->str_longlen = t2->str_longlen;
	if (t1->str_shortlen > t2->str_shortlen)
		t1->str_shortlen = t2->str_shortlen;
}
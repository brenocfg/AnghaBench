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
struct TYPE_3__ {int /*<<< orphan*/  str_shortlen; scalar_t__ str_longlen; scalar_t__ str_numstr; } ;
typedef  TYPE_1__ STRFILE ;

/* Variables and functions */

__attribute__((used)) static void
zero_tbl(STRFILE *tp)
{
	tp->str_numstr = 0;
	tp->str_longlen = 0;
	tp->str_shortlen = ~0;
}
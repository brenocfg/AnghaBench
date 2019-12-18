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
typedef  size_t u_long ;
struct TYPE_4__ {size_t fieldcnt; int /*<<< orphan*/ * fields; } ;
typedef  TYPE_1__ LINE ;

/* Variables and functions */
 int mbscoll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmp(LINE *lp1, u_long fieldno1, LINE *lp2, u_long fieldno2)
{
	if (lp1->fieldcnt <= fieldno1)
		return (lp2->fieldcnt <= fieldno2 ? 0 : 1);
	if (lp2->fieldcnt <= fieldno2)
		return (-1);
	return (mbscoll(lp1->fields[fieldno1], lp2->fields[fieldno2]));
}
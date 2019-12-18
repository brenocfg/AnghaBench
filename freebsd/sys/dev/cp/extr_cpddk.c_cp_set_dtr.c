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
struct TYPE_3__ {int l193; int l33; int /*<<< orphan*/  l73; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ e ;

/* Variables and functions */
 int /*<<< orphan*/  l (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void cp_set_dtr(e*a,int m){a->l193=(m!=0);{if(!(
a->l193))goto l361;a->l33|=1;goto l357;l361:;a->l33&=~1;l357:;}l(a->d
,a->l73,a->l33);}
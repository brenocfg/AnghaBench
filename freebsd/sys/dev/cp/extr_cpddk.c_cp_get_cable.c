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
struct TYPE_3__ {int f; int l81; int p; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ e ;

/* Variables and functions */
 int u (int /*<<< orphan*/ ,int) ; 

int cp_get_cable(e*a){{if(!(a->f==1))goto
l841;switch(u(a->d,a->l81)&70){case 0:return 3;case 2:return 2;case 4
:return 1;case 6:return 0;case 10:return 4;default:return 9;}goto l420
;l841:;{if(!(a->f==3))goto l838;return(u(a->d,8)>>a->p&16)?11:10;goto
l844;l838:;{if(!(a->f==4))goto l840;return 10;goto l846;l840:;return 0
;l846:;}l844:;}l420:;}}
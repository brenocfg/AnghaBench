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
struct TYPE_3__ {int f; int l134; int l41; int /*<<< orphan*/  l62; int /*<<< orphan*/  d; int /*<<< orphan*/  l31; scalar_t__ l52; scalar_t__ l38; } ;
typedef  TYPE_1__ e ;

/* Variables and functions */
 int /*<<< orphan*/  l (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void cp_set_scrambler(e*a,int m){{if(!(a->f!=
2&&!(a->f==3&&a->l38)))goto l685;return;l685:;}{if(!(a->l38&&(a->l52
||!a->l31)))goto l543;m=0;l543:;}a->l134=(m!=0);{if(!(a->l134))goto
l687;a->l41|=16;goto l542;l687:;a->l41&=~16;l542:;}l(a->d,a->l62,a->
l41);}
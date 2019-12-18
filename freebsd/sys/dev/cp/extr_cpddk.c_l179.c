#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int l116; TYPE_2__* k; int /*<<< orphan*/  l30; } ;
typedef  TYPE_1__ s ;
typedef  int /*<<< orphan*/  l72 ;
struct TYPE_10__ {int* j; int* l40; } ;
struct TYPE_9__ {int f; int p; int v; int j; TYPE_3__ o; int /*<<< orphan*/  l46; int /*<<< orphan*/  l34; TYPE_1__* d; } ;
typedef  TYPE_2__ e ;

/* Variables and functions */
 int /*<<< orphan*/  l (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  l138 (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void l179(e*a,l72*l149){s*b=a->d;e*h;int c;{if
(!(a->f!=3||!a->l34))goto l247;return;l247:;}{if(!(!b->l30))goto l248
;memset(&a->o,0,sizeof(a->o));goto l249;l248:;memcpy(&a->o,l149,
sizeof(a->o));l249:;}a->o.j[0]=0;{if(!(!a->l46))goto l250;a->o.j[16]=
0;l250:;}{c=1;l251:if(!(c<32))goto l252;goto l253;l894:++c;goto l251;
l253:{if(!(a->o.j[c]&=31))goto l688;{{if(!((b->k+2)->f!=3))goto l680;
a->o.l40[c]&=1;goto l677;l680:;a->o.l40[c]&=3;l677:;}{h=b->k;l673:if(
!(h<b->k+4))goto l152;goto l670;l209:++h;goto l673;l670:{{if(!(h->f!=
3))goto l663;goto l209;l663:;}{if(!(h->p==a->o.l40[c]&&a->o.j[c]==16
&&!h->l46))goto l660;{a->o.j[c]=0;goto l152;}l660:;}{if(!((h->v==a->o
.l40[c]&&((h->j>>a->o.j[c])&1))||(h->v==a->p&&((h->j>>c)&1))))goto
l658;{a->o.j[c]=0;goto l152;}l658:;}{if(!(h->p==a->p))goto l611;goto
l152;l611:;}}goto l209;l152:;}}l688:;}goto l894;l252:;}l(b,8,b->l116&
~1);l(b,28,a->p<<5);l(b,31,139);{c=1;l606:if(!(c<32))goto l602;goto
l601;l605:++c;goto l606;l601:l(b,31,(!a->o.j[c])?141:(a->o.l40[c]<<5)|
a->o.j[c]);goto l605;l602:;}l(b,8,b->l116);{c=0;l600:if(!(c<4))goto
l598;goto l597;l196:c++;goto l600;l597:{{if(!((b->k+c)->f!=3))goto
l594;goto l196;l594:;}l138(b->k+c);}goto l196;l598:;}}
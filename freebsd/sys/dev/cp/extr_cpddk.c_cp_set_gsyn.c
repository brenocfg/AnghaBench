#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  l30; TYPE_2__* k; } ;
typedef  TYPE_1__ s ;
struct TYPE_7__ {int f; int l26; unsigned char l61; int l41; int /*<<< orphan*/  l62; TYPE_1__* d; int /*<<< orphan*/  l64; int /*<<< orphan*/  p; int /*<<< orphan*/  l31; } ;
typedef  TYPE_2__ e ;

/* Variables and functions */
 int /*<<< orphan*/  l (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  l68 (TYPE_2__*) ; 

void cp_set_gsyn(e*a,int l78){switch(a->f){case 3:{unsigned char
l26=0;e*h;s*b=a->d;{if(!(a->l31&&l78!=0))goto l540;l78=1;l540:;}
switch(l78){default:l78=0;l26=0;break;case 1:l78=2+a->p;l26=1+a->p;
break;case 2:l26=1;break;case 3:l26=2;break;case 4:l26=3;{if(!(b->k[2
].f!=3))goto l691;return;l691:;}break;case 5:l26=4;{if(!(b->k[3].f!=3
))goto l692;return;l692:;}break;}{h=b->k;l693:if(!(h<b->k+4))goto l536
;goto l535;l212:h++;goto l693;l535:{{if(!(h->f!=3||(!b->l30&&h!=a)))goto
l533;goto l212;l533:;}l(b,h->l64,h->l26&~128);h->l26&=~7;h->l26|=l26;
h->l61=(unsigned char)l78;l(b,h->l64,h->l26);}goto l212;l536:;}}break
;case 2:{if(!(l78))goto l699;{a->l61=1;a->l41|=8;}goto l703;l699:;{a
->l61=0;a->l41&=~8;}l703:;}l(a->d,a->l62,a->l41);break;case 4:case 7:
case 8:{if(!(l78))goto l704;a->l61=1;goto l705;l704:;a->l61=0;l705:;}
l68(a);break;}}
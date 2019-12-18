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
struct TYPE_6__ {TYPE_2__* k; int /*<<< orphan*/  l30; } ;
typedef  TYPE_1__ s ;
struct TYPE_7__ {int f; scalar_t__ v; scalar_t__ p; unsigned long j; int /*<<< orphan*/  l34; int /*<<< orphan*/  l31; TYPE_1__* d; } ;
typedef  TYPE_2__ e ;

/* Variables and functions */
 int /*<<< orphan*/  i (TYPE_2__*,int,unsigned char) ; 
 scalar_t__ l198 (TYPE_2__*,int) ; 

__attribute__((used)) static void
l138(e*a){s*b=a->d;e*h;unsigned long l66;int c;{if(!(a->l31))goto l722
;{l66=0;}goto l728;l722:;{if(!(a->l34))goto l724;{l66=~1;{h=b->k;l710
:if(!(h<b->k+4))goto l702;goto l701;l709:++h;goto l710;l701:{if(!((h
->f==3||h->f==6)&&h->v==a->p))goto l697;l66&=~h->j;l697:;}goto l709;
l702:;}{if(!(b->l30))goto l690;{c=1;l689:if(!(c<32))goto l682;goto
l676;l678:++c;goto l689;l676:{if(!((l66>>c&1)&&l198(a,c)))goto l672;
l66&=~(1<<c);l672:;}goto l678;l682:;}l690:;}}goto l671;l724:;{if(!(b
->l30))goto l668;{l66=a->p?(b->k[0].j|b->k[1].j):0;}goto l667;l668:;
l66=~a->j;l667:;}l671:;}l728:;}i(a,38,(unsigned char)(l66&254));i(a,
38+1,(unsigned char)(l66>>8));i(a,38+2,(unsigned char)(l66>>16));i(a,
38+3,(unsigned char)(l66>>24));;}
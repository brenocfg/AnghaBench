#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int l30; TYPE_2__* k; } ;
typedef  TYPE_1__ s ;
struct TYPE_14__ {int f; unsigned long j; size_t v; scalar_t__ l31; scalar_t__ p; int l33; int l73; int /*<<< orphan*/  y; int /*<<< orphan*/  o; scalar_t__ l34; TYPE_1__* d; int /*<<< orphan*/  l38; int /*<<< orphan*/  l46; } ;
typedef  TYPE_2__ e ;

/* Variables and functions */
 int /*<<< orphan*/  cp_set_baud (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i (TYPE_2__*,int,unsigned char) ; 
 int /*<<< orphan*/  l (TYPE_1__*,int,unsigned char) ; 
 int /*<<< orphan*/  l138 (TYPE_2__*) ; 
 int /*<<< orphan*/  l168 (TYPE_1__*) ; 
 int /*<<< orphan*/  l179 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l610 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  l686 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int u (TYPE_1__*,int /*<<< orphan*/ ) ; 

void cp_set_ts(
e*a,unsigned long j){s*b=a->d;e*h;int c;{if(!(a->f!=3&&a->f!=6))goto
l574;return;l574:;}a->j=j&4294967294UL;{if(!(b->k[a->v].l31||b->k[a->
v].f!=3))goto l573;a->j=0;l573:;}{if(!(!b->k[a->v].l46))goto l570;a->
j&=~(1<<16);l570:;}{h=b->k;l569:if(!(h<b->k+4))goto l567;goto l564;
l568:++h;goto l569;l564:{if(!((h->f==3||h->f==6)&&h->p!=a->p&&h->v==a
->v))goto l562;a->j&=~h->j;l562:;}goto l568;l567:;}{if(!(b->l30&&b->k
->l34))goto l561;{c=1;l557:if(!(c<32))goto l525;goto l380;l526:++c;
goto l557;l380:{if(!((a->j>>c&1)))goto l490;{l610(b->k+a->v,c);l686(b
->k+a->v,c);}l490:;}goto l526;l525:;}l561:;}{if(!((a->j&65534)==0&&a
->l31!=0))goto l348;a->l33|=16;goto l466;l348:;a->l33&=~16;l466:;}l(a
->d,a->l73,a->l33);;{if(!(a->l38))goto l377;{int c;int j;{if(!(a->l31
))goto l378;j=4294967295UL;goto l379;l378:;j=a->j;l379:;}l(a->d,9,a->
p<<6);{c=1;l395:if(!(c<32))goto l323;goto l411;l396:++c;goto l395;
l411:{{l338:if(!(u(a->d,0)&1))goto l413;{outb(128,0);}goto l338;l413:
;}l(a->d,10,(unsigned char)(j>>c&1));}goto l396;l323:;}{l407:if(!(u(a
->d,0)&1))goto l442;{outb(128,0);}goto l407;l442:;}l(a->d,10,(
unsigned char)j&1);{c=1;l325:if(!(c<32))goto l426;goto l412;l425:++c;
goto l325;l412:{{l275:if(!(u(a->d,0)&1))goto l492;{outb(128,0);}goto
l275;l492:;}l(a->d,10,(unsigned char)(j>>c&1));}goto l425;l426:;}{
l263:if(!(u(a->d,0)&1))goto l444;{outb(128,0);}goto l263;l444:;}l(a->
d,10,(unsigned char)j&1);}l377:;}{if(!(a->f==3))goto l427;{i(a,34,(
unsigned char)(a->j&254));i(a,34+1,(unsigned char)(a->j>>8));i(a,34+2
,(unsigned char)(a->j>>16));i(a,34+3,(unsigned char)(a->j>>24));i(a,
43,(unsigned char)(a->j&254));i(a,43+1,(unsigned char)(a->j>>8));i(a,
43+2,(unsigned char)(a->j>>16));i(a,43+3,(unsigned char)(a->j>>24));}
l427:;}{if(!(!a->l34))goto l473;{l138(b->k+0);l138(b->k+1);}goto l294
;l473:;{{if(!(b->l30!=2))goto l456;l168(b);l456:;}{h=b->k;l487:if(!(h
<b->k+4))goto l489;goto l455;l471:h++;goto l487;l455:l179(h,&h->o);
goto l471;l489:;}}l294:;}cp_set_baud(a,a->y);}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int l125; TYPE_3__* k; scalar_t__ g; scalar_t__ l115; scalar_t__ l94; int /*<<< orphan*/  l30; } ;
typedef  TYPE_1__ s ;
struct TYPE_16__ {scalar_t__* l97; scalar_t__* l155; scalar_t__ l94; } ;
typedef  TYPE_2__ l172 ;
struct TYPE_17__ {int f; unsigned long l35; unsigned long l36; int l144; unsigned long l70; size_t p; unsigned long* l123; unsigned long* l124; int /*<<< orphan*/  l38; scalar_t__* l75; scalar_t__* l82; scalar_t__ l104; scalar_t__ l608; scalar_t__ l97; scalar_t__ l155; scalar_t__ x; } ;
typedef  TYPE_3__ e ;

/* Variables and functions */
 int /*<<< orphan*/  cp_led (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_mux (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  l157 (TYPE_3__*) ; 
 int /*<<< orphan*/  l165 (TYPE_3__*) ; 
 int /*<<< orphan*/  l210 (TYPE_3__*) ; 
 int l57 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  l741 (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void cp_reset(s*b,l172*l60,unsigned
long l69){e*a;{if(!(!b->g))goto l856;return;l856:;}{if(!(l60))goto
l857;memset(l60,0,sizeof(l172));l857:;} * (volatile unsigned long* )(
(b)->g+8)=262144; * (volatile unsigned short* )((b)->g+1032)=65535; *
(volatile unsigned short* )((b)->g+1024)=255; * (volatile unsigned
short* )((b)->g+1028)=255; * (volatile unsigned long* )((b)->g+768)=
4194304;l(b,0,b->l125&~4);cp_led(b,0); * (volatile unsigned long* )((
b)->g+12)=(128/32-1)<<28|(128/32-1)<<24|(128/32-1)<<20|(128/32-1)<<16
|(128/32-1)<<12|(128/32-1)<<8|(128/32-1)<<4|(128/32-1); * (volatile
unsigned long* )((b)->g+16)=(128/32-1)<<16; * (volatile unsigned long
 * )((b)->g+68)=1108361216; * (volatile unsigned long* )((b)->g+72)=
3740719104UL; * (volatile unsigned long* )((b)->g+52)=404232216; * (
volatile unsigned long* )((b)->g+76)=7;cp_set_mux(b,b->l30);{if(!(l60
))goto l858;{b->l94=l60->l94; * (volatile unsigned long* )((b)->g+64)=
l69+((char* )b->l94-(char* )l60);}l858:;}b->l115=0;{a=b->k;l859:if(!(
a<b->k+4))goto l861;goto l862;l860:++a;goto l859;l862:{{if(!(a->f==2))goto
l863;l165(a);goto l864;l863:;{if(!(a->f==3))goto l441;l210(a);l441:;}
l864:;}l157(a);a->l35=0; * (volatile unsigned long* )((a)->x+8)=a->
l35;a->l36=0; * (volatile unsigned long* )((a)->x+16)=a->l36;a->l144=
1; * (volatile unsigned long* )((a)->x+84)=a->l70=~0; * (volatile
unsigned long* )((a)->x+28)=520552703; * (volatile unsigned long* )((
a)->x+32)=520552703;{if(!(l60))goto l885;{a->l155=l60->l155[a->p];a->
l97=l60->l97[a->p];( * (a)->l123)=l69+((char* )a->l155-(char* )l60);(
 * (a)->l124)=l69+((char* )a->l97-(char* )l60);;}l885:;}a->l608=0;a->
l104=0;( * (a)->l82)=0;( * (a)->l75)=0;}goto l860;l861:;} * (volatile
unsigned long* )((b)->g+0)=4279239169UL;{a=b->k;l887:if(!(a<b->k+4))goto
l443;goto l889;l223:++a;goto l887;l889:{{if(!(a->f!=3||!a->l38||l57(a
,15)!=163))goto l891;goto l223;l891:;}l741(a);}goto l223;l443:;}}
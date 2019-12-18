#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t l45; unsigned char** l151; scalar_t__* l75; scalar_t__* l154; size_t l51; int* l82; int p; TYPE_2__* d; TYPE_1__* l42; int /*<<< orphan*/  l52; void** l79; } ;
typedef  TYPE_3__ e ;
struct TYPE_7__ {scalar_t__ g; } ;
struct TYPE_6__ {int /*<<< orphan*/  w; int /*<<< orphan*/  t; } ;

/* Variables and functions */
 int /*<<< orphan*/  cp_transmit_space (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

int cp_send_packet(e*a,unsigned char*l99
,int w,void*l79){{if(!(!cp_transmit_space(a)))goto l714;return-1;l714
:;}{if(!(w<=0||w>1664-1))goto l706;return-2;l706:;}a->l79[a->l45]=l79
;{if(!(l99!=a->l151[a->l45]))goto l698;memcpy(a->l151[a->l45],l99,w);
l698:;} * (volatile unsigned long* )&a->l42[a->l45].t=0;outb(128,0); *
(volatile unsigned long* )&a->l42[a->l45].w=2147483648UL|1073741824|w
<<16;{if(!(a->l52))goto l694; * (volatile unsigned long* )&a->l42[a->
l45].w|=536870912;l694:;}outb(128,0); * (volatile unsigned long* )&a
->l42[(a->l45+4-1)%4].w&=~1073741824;outb(128,0);;{if(!(( * (a)->l75)==
0))goto l645;{;( * (a)->l75)=a->l154[a->l51];outb(128,0);( * (a)->l82
)=524288;outb(128,0); * (volatile unsigned long* )((a->d)->g+0)=513;}
goto l650;l645:;{if(!(a->l51==a->l45))goto l648;{; * (volatile
unsigned long* )((a->d)->g+0)=1024<<a->p;}l648:;}l650:;}outb(128,0);a
->l45=(a->l45+1)%4;return 0;}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__* l589; scalar_t__* l751; TYPE_2__* l42; TYPE_1__* l32; } ;
typedef  TYPE_3__ l211 ;
struct TYPE_18__ {int f; unsigned long* l67; unsigned long* l154; int l35; int l43; unsigned long* l207; unsigned long* l197; size_t l28; int l70; int l36; unsigned long* l130; int* l82; scalar_t__ x; TYPE_6__* d; int /*<<< orphan*/  l44; int /*<<< orphan*/  l144; TYPE_1__* l32; scalar_t__ l51; scalar_t__ l45; scalar_t__* l79; TYPE_2__* l42; scalar_t__* l151; scalar_t__* l136; scalar_t__* l75; int /*<<< orphan*/  y; int /*<<< orphan*/  v; int /*<<< orphan*/  l145; int /*<<< orphan*/  l52; } ;
typedef  TYPE_4__ e ;
struct TYPE_19__ {int f; scalar_t__ g; } ;
struct TYPE_16__ {int /*<<< orphan*/  t; int /*<<< orphan*/  l99; int /*<<< orphan*/  w; int /*<<< orphan*/  l88; } ;
struct TYPE_15__ {int /*<<< orphan*/  l88; int /*<<< orphan*/  t; int /*<<< orphan*/  l99; int /*<<< orphan*/  w; } ;

/* Variables and functions */
 int /*<<< orphan*/  cp_set_baud (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_dir (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_dtr (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_nrzi (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_phony (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_rts (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  l165 (TYPE_4__*) ; 

void
cp_start_chan(e*a,int l208,int l191,l211*l49,unsigned long l69){int c
;unsigned long l96=0;{if(!(!a->f))goto l583;return;l583:;}{if(!(l49))goto
l531;{;a->l32=l49->l32;a->l42=l49->l42;{c=0;l464:if(!(c<64))goto l336
;goto l335;l273:++c;goto l464;l335:a->l67[c]=l69+((char* )(a->l32+c)-
(char* )l49);goto l273;l336:;}{c=0;l320:if(!(c<4))goto l288;goto l257
;l305:++c;goto l320;l257:a->l154[c]=l69+((char* )(a->l42+c)-(char* )l49
);goto l305;l288:;};{c=0;l234:if(!(c<64))goto l546;goto l514;l906:++c
;goto l234;l514: * (volatile unsigned long* )&a->l32[c].l88=a->l67[(c
+1)%64];goto l906;l546:;}{c=0;l462:if(!(c<4))goto l312;goto l351;l319
:++c;goto l462;l351: * (volatile unsigned long* )&a->l42[c].l88=a->
l154[(c+1)%4];goto l319;l312:;}}l531:;}{if(!(a->d->f==2))goto l265;{a
->l35|=12; * (volatile unsigned long* )((a)->x+8)=a->l35;a->l43=
2097152;}l265:;}a->l43|=574914560; * (volatile unsigned long* )((a)->
x+12)=a->l43;cp_set_phony(a,a->l52); * (volatile unsigned long* )((a)->
x+64)=32768|(1664/32-1);{if(!(a->f==2))goto l334;l165(a);l334:;}a->
l35|=2147483648UL; * (volatile unsigned long* )((a)->x+8)=a->l35;
cp_set_nrzi(a,a->l145);cp_set_dir(a,a->v);cp_set_baud(a,a->y);
cp_set_dtr(a,0);cp_set_rts(a,0);( * (a)->l75)=0;{c=0;l328:if(!(c<64))goto
l902;goto l790;l297:++c;goto l328;l790:{{if(!(l49))goto l752;{a->l136
[c]=l49->l751[c];a->l207[c]=l69+((char* )a->l136[c]-(char* )l49); * (
volatile unsigned long* )&a->l32[c].w=1664<<16; * (volatile unsigned
long* )&a->l32[c].l99=a->l207[c];}l752:;} * (volatile unsigned long* )&
a->l32[c].t=0;}goto l297;l902:;}{c=0;l718:if(!(c<4))goto l696;goto
l674;l595:++c;goto l718;l674:{{if(!(l49))goto l664;{a->l151[c]=l49->
l589[c];a->l197[c]=l69+((char* )a->l151[c]-(char* )l49); * (volatile
unsigned long* )&a->l42[c].w=2147483648UL|1073741824; * (volatile
unsigned long* )&a->l42[c].l99=a->l197[c];}l664:;} * (volatile
unsigned long* )&a->l42[c].t=0;a->l79[c]=0;}goto l595;l696:;}{if(!(
l49))goto l652;;l652:;}a->l28=0;a->l51=0;a->l45=a->l51; * (volatile
unsigned long* )&a->l32[64-1].l88=a->l67[64-1];{if(!(l208))goto l640;
{{if(!(!a->l144))goto l545;{a->l70&=~65536;}goto l538;l545:;{a->l70&=
~65536; * (volatile unsigned long* )((a)->x+84)=a->l70;}l538:;}l96|=
16777216;}l640:;}{if(!(l191))goto l528;{a->l36|=134217728; * (
volatile unsigned long* )((a)->x+16)=a->l36;{if(!(!a->l144))goto l517
;{a->l70&=~2;}goto l513;l517:;{a->l70&=~2; * (volatile unsigned long*
)((a)->x+84)=a->l70;}l513:;}l96|=65536;{if(!(a->f==2))goto l497;l(a->
d,a->l44,255);l497:;};( * (a)->l130)=a->l67[a->l28];( * (a)->l82)=
1048576; * (volatile unsigned long* )((a->d)->g+0)=513;}l528:;} * (
volatile unsigned long* )((a)->x+0)=l96;}
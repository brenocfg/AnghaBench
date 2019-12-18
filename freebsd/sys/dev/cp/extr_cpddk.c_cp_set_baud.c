#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int f; int l41; int y; unsigned long j; int l35; int l33; int l43; scalar_t__ x; scalar_t__ l53; int /*<<< orphan*/  l73; TYPE_2__* d; scalar_t__ l146; scalar_t__ l52; int /*<<< orphan*/  l62; scalar_t__ l31; } ;
typedef  TYPE_1__ e ;
struct TYPE_5__ {int l80; } ;

/* Variables and functions */
 int /*<<< orphan*/  l (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  l141 (int,int,int*,int*) ; 

void cp_set_baud(e
 *a,int y){int l54,l50;{if(!(a->f==2||((a->f==3)&&a->l31)))goto l240;
{int l92=(y+32000)/64000*64;{if(!(a->l52))goto l236;l92=2048;l236:;}a
->l41&=~7;{if(!(!l92||l92>1024))goto l235;{a->l41|=0;a->y=2048000;}
goto l232;l235:;{if(!(l92>512))goto l231;{a->l41|=2;a->y=1024000;}
goto l229;l231:;{if(!(l92>256))goto l228;{a->l41|=3;a->y=512000;}goto
l901;l228:;{if(!(l92>128))goto l880;{a->l41|=4;a->y=256000;}goto l837
;l880:;{if(!(l92>64))goto l524;{a->l41|=5;a->y=128000;}goto l522;l524
:;{a->l41|=6;a->y=64000;}l522:;}l837:;}l901:;}l229:;}l232:;}l(a->d,a
->l62,a->l41);}goto l520;l240:;{if(!((a->f==3||a->f==6)&&!a->l52))goto
l518;{unsigned long l558=a->j;int c;a->y=0;{c=0;l516:if(!(c<32))goto
l512;goto l494;l515:++c;goto l516;l494:{if(!((l558>>c)&1))goto l500;a
->y+=64000;l500:;}goto l515;l512:;}}goto l478;l518:;{if(!(a->f==3&&a
->l52))goto l383;{a->y=2048000;}goto l347;l383:;a->y=y;l347:;}l478:;}
l520:;}a->l35&=~55;{if(!(a->f==4||a->f==7||a->f==8))goto l385;{a->y=a
->d->l80;a->l35|=12;l50=l54=0;}goto l345;l385:;{if(!(!a->y||a->f!=1))goto
l387;{a->l146=0;{if(!(a->f==1))goto l344;a->l53=0;l344:;}l50=l54=0;a
->l33|=4;}goto l389;l387:;{if(!(a->l146))goto l341;{a->l35|=54;l141(a
->d->l80/16,a->y,&l50,&l54);a->l33&=~4;}goto l340;l341:;{if(!(a->l53))goto
l393;{a->l35|=55;l141(a->d->l80,a->y,&l50,&l54);a->l33&=~4;}goto l317
;l393:;{a->l35|=48;l141(a->d->l80,a->y,&l50,&l54);a->l33&=~4;}l317:;}
l340:;}l389:;}l345:;}l(a->d,a->l73,a->l33&~4); * (volatile unsigned
long* )((a)->x+8)=a->l35; * (volatile unsigned long* )((a)->x+44)=l50
<<8|l54;l(a->d,a->l73,a->l33);{if(!(a->f==1&&a->l53))goto l415;a->l43
|=256;goto l416;l415:;a->l43&=~256;l416:;} * (volatile unsigned long*
)((a)->x+12)=a->l43;}
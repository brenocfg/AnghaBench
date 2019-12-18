#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ l100; scalar_t__ l120; scalar_t__ l110; scalar_t__ l119; scalar_t__ l108; scalar_t__ l117; scalar_t__ l89; scalar_t__ l101; scalar_t__ l103; scalar_t__ l121; scalar_t__ l112; scalar_t__ l47; } ;
struct TYPE_9__ {int /*<<< orphan*/  l100; int /*<<< orphan*/  l120; int /*<<< orphan*/  l110; int /*<<< orphan*/  l119; int /*<<< orphan*/  l108; int /*<<< orphan*/  l117; int /*<<< orphan*/  l89; int /*<<< orphan*/  l101; int /*<<< orphan*/  l103; int /*<<< orphan*/  l121; int /*<<< orphan*/  l112; int /*<<< orphan*/  l47; } ;
struct TYPE_11__ {int l55; int t; int l105; unsigned int l109; scalar_t__ l161; TYPE_3__ n; TYPE_2__ l29; TYPE_3__* l118; scalar_t__ l38; TYPE_1__* d; scalar_t__ l58; int /*<<< orphan*/  l46; int /*<<< orphan*/  l31; } ;
typedef  TYPE_4__ e ;
struct TYPE_8__ {scalar_t__ l30; } ;

/* Variables and functions */
 short l57 (TYPE_4__*,int) ; 
 unsigned char l90 (TYPE_4__*,int,int) ; 

__attribute__((used)) static void l188(e*a){unsigned char l77,
l150;unsigned l47,l153,l58,l182,l111,l131;++a->l55;{if(!(!a->l161&&a
->l55<=1))goto l523;return;l523:;}a->t=0;l77=l90(a,6,255);l131=0;{if(
!(l77&2))goto l707;a->t|=64;l707:;}{if(!(l77&8))goto l708;a->t|=8;
l708:;}l47=(((short)(l57(a,0))<<8)|(l57(a,1)));l153=0;l58=0;l182=0;{
if(!(!a->l31))goto l519;{l150=l57(a,30);{if(!(!a->l46&&(l77&128)))goto
l711;a->t|=256;l711:;}{if(!(!a->l46&&(l77&64)))goto l712;a->t|=512;
l712:;}{if(!(l77&4))goto l713;a->t|=2;l713:;}{if(!(l150&4))goto l717;
{a->t|=32;++l131;}l717:;}{if(!((!a->l46&&(l150&2))||(a->l58&&(l150&1))))goto
l511;{a->t|=1024;++l131;}l511:;}l153=(((short)(l57(a,2))<<4&4032)|(
l57(a,4))>>2);l58=(((short)(l57(a,2))<<8&768)|(l57(a,3)));l182=(((
short)(l57(a,4))<<8&768)|(l57(a,5)));{if(!((a->d->l30||a->l38)&&(l77&
16)))goto l719;++a->n.l120;l719:;}}l519:;}{if(!(a->t&64))goto l510;a
->t=64;goto l723;l510:;{if(!(a->t&8))goto l499;a->t=8;goto l725;l499:
;{if(!(a->t&32))goto l498;a->t=32;goto l727;l498:;{if(!(a->t&1024))goto
l493;a->t&=~(512|256);l493:;}l727:;}l725:;}l723:;}{if(!(!a->t))goto
l470;a->t=1;l470:;}a->n.l47+=l47;a->n.l112+=l153;{if(!(a->l58))goto
l732;{a->n.l121+=l58;a->n.l103+=l182;}l732:;}l111=l153;{if(!(a->l58))goto
l748;l111+=l58;l748:;}{if(!(l77&(8|2)))goto l744;++a->n.l101;goto l374
;l744:;{{if(!(l47))goto l746;++a->n.l89;l746:;}{if(!(l111||l131||((a
->d->l30||a->l38)&&(l77&16))))goto l747;++a->n.l117;l747:;}{if(!(l131
))goto l753;++a->n.l110;l753:;}{if(!(l47>=2048||l111>=832))goto l749;
++a->n.l119;goto l754;l749:;{{if(!(l111>1))goto l756;++a->n.l108;l756
:;}++a->l105;a->l109+=l47+l111;}l754:;}}l374:;}{if(!(a->l55%60==0))goto
l757;{{if(!(a->l109>a->l105*2048/1000))goto l773;++a->n.l100;l773:;}a
->l105=0;a->l109=0;}l757:;}{if(!(a->l55>15*60))goto l769;{int c;{c=47
;l384:if(!(c>0))goto l772;goto l776;l771:--c;goto l384;l776:a->l118[c
]=a->l118[c-1];goto l771;l772:;}a->l118[0]=a->n;a->l29.l47+=a->n.l47;
a->l29.l112+=a->n.l112;a->l29.l121+=a->n.l121;a->l29.l103+=a->n.l103;
a->l29.l101+=a->n.l101;a->l29.l89+=a->n.l89;a->l29.l117+=a->n.l117;a
->l29.l108+=a->n.l108;a->l29.l119+=a->n.l119;a->l29.l110+=a->n.l110;a
->l29.l120+=a->n.l120;a->l29.l100+=a->n.l100;a->n.l47=0;a->n.l112=0;a
->n.l121=0;a->n.l103=0;a->n.l101=0;a->n.l89=0;a->n.l117=0;a->n.l108=0
;a->n.l119=0;a->n.l110=0;a->n.l120=0;a->n.l100=0;a->l161+=a->l55;a->
l55=0;}l769:;}}
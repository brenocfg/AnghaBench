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
struct TYPE_6__ {int l669; int l95; int l86; int l148; int l616; scalar_t__ l142; int /*<<< orphan*/  l621; scalar_t__* l184; scalar_t__ l122; TYPE_2__* d; } ;
typedef  TYPE_1__ e ;
struct TYPE_7__ {int f; } ;

/* Variables and functions */
 int /*<<< orphan*/  l (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  l68 (TYPE_1__*) ; 
 int u (TYPE_2__*,int) ; 

void cp_e3_timer(e*a){unsigned char l126;unsigned
long l140;{if(!(a->d->f!=2))goto l815;return;l815:;}l(a->d,11,0);l140
=u(a->d,11);l140|=u(a->d,12)<<8;l140|=u(a->d,13)<<16;l126=u(a->d,9);l
(a->d,9,a->l669|1);{if(!(l126&2))goto l816;{{if(!(a->l122&&(a->l95&2)!=
0&&!a->l86))goto l817;{a->l86=1;l68(a);}l817:;}a->l95=2;}goto l819;
l816:;{{if(!(a->l122&&(a->l95&2)==0&&a->l86))goto l409;{a->l86=0;l68(
a);}l409:;}a->l95=0;}l819:;}{if(!(l126&1))goto l849;a->l95|=4;l849:;}
{if(!(l126&4&&!(l126&2)))goto l843;a->l95|=8;l843:;}{if(!(!(a->l95&2)))goto
l851;a->l142+=l140;l851:;}a->l148++;{if(!(a->l148>5*60*15))goto l845;
{int c;{c=47;l439:if(!(c>0))goto l848;goto l873;l847:c--;goto l439;
l873:a->l184[c]=a->l184[c-1];goto l847;l848:;}a->l184[0]=a->l142;a->
l621+=a->l142;a->l616+=a->l148/5;a->l142=0;a->l148=0;}l845:;}}
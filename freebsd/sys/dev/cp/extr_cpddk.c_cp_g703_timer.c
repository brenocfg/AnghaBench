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
struct TYPE_8__ {scalar_t__ l100; scalar_t__ l120; scalar_t__ l110; scalar_t__ l119; scalar_t__ l108; scalar_t__ l117; scalar_t__ l89; scalar_t__ l101; scalar_t__ l103; scalar_t__ l121; scalar_t__ l112; scalar_t__ l47; } ;
struct TYPE_6__ {int /*<<< orphan*/  l100; int /*<<< orphan*/  l120; int /*<<< orphan*/  l110; int /*<<< orphan*/  l119; int /*<<< orphan*/  l108; int /*<<< orphan*/  l117; int /*<<< orphan*/  l89; int /*<<< orphan*/  l101; int /*<<< orphan*/  l103; int /*<<< orphan*/  l121; int /*<<< orphan*/  l112; int /*<<< orphan*/  l47; } ;
struct TYPE_7__ {int l55; int t; int l105; int l109; scalar_t__ l161; TYPE_3__ n; TYPE_1__ l29; TYPE_3__* l118; int /*<<< orphan*/  l44; int /*<<< orphan*/  d; } ;
typedef  TYPE_2__ e ;

/* Variables and functions */
 int cp_get_cd (TYPE_2__*) ; 
 int /*<<< orphan*/  l (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 unsigned char u (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cp_g703_timer(e*a){unsigned char l84;int l158;++a
->l55;{if(!(!a->l161&&a->l55<=1))goto l386;return;l386:;}a->t=0;l84=u
(a->d,a->l44);l(a->d,a->l44,l84);l158=cp_get_cd(a);{if(!(l84&1))goto
l775;++a->n.l47;l775:;}{if(!(!l158))goto l777;a->t|=64;l777:;}{if(!(
l84&2))goto l388;a->t|=4096;l388:;}{if(!(l84&16))goto l789;a->t|=2048
;l789:;}{if(!(!a->t))goto l394;a->t=1;l394:;}{if(!(!l158||(l84&16)))goto
l791;++a->n.l101;goto l792;l791:;{{if(!(l84&1))goto l793;++a->n.l89;
l793:;}++a->l105;{if(!(l158&&(l84&1)))goto l794;++a->l109;l794:;}}
l792:;}{if(!(a->l55/60==0))goto l795;{{if(!(a->l109*2>a->l105))goto
l796;++a->n.l100;l796:;}a->l105=0;a->l109=0;}l795:;}{if(!(a->l55>15*
60))goto l398;{int c;{c=47;l800:if(!(c>0))goto l812;goto l408;l811:--
c;goto l800;l408:a->l118[c]=a->l118[c-1];goto l811;l812:;}a->l118[0]=
a->n;a->l29.l47+=a->n.l47;a->l29.l112+=a->n.l112;a->l29.l121+=a->n.
l121;a->l29.l103+=a->n.l103;a->l29.l101+=a->n.l101;a->l29.l89+=a->n.
l89;a->l29.l117+=a->n.l117;a->l29.l108+=a->n.l108;a->l29.l119+=a->n.
l119;a->l29.l110+=a->n.l110;a->l29.l120+=a->n.l120;a->l29.l100+=a->n.
l100;memset(&a->n,0,sizeof(a->n));a->l161+=a->l55;a->l55=0;}l398:;}}
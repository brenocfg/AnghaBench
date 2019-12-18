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
struct TYPE_6__ {int l174; TYPE_2__* k; scalar_t__ l30; } ;
typedef  TYPE_1__ s ;
struct TYPE_7__ {int f; int l46; int /*<<< orphan*/  l34; } ;
typedef  TYPE_2__ e ;

/* Variables and functions */
 int /*<<< orphan*/  cp_set_use16 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  l225 (TYPE_2__*) ; 

void l195(s*b,int m){e*h;{if(!(!b->k->l34))goto l798;return;
l798:;}b->l174=(m&&b->l30)?1:0;{h=b->k;l784:if(!(h<b->k+4))goto l782;
goto l778;l220:++h;goto l784;l778:{{if(!(h->f!=3))goto l551;goto l220
;l551:;}cp_set_use16(h,m?m:h->l46);l225(h);}goto l220;l782:;}}
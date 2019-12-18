#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ l30; TYPE_2__* k; } ;
typedef  TYPE_1__ s ;
struct TYPE_9__ {int f; int v; int p; int j; int /*<<< orphan*/  l34; TYPE_1__* d; int /*<<< orphan*/  l31; } ;
typedef  TYPE_2__ e ;

/* Variables and functions */
 int /*<<< orphan*/  cp_set_ts (TYPE_2__*,int) ; 
 int /*<<< orphan*/  l157 (TYPE_2__*) ; 
 scalar_t__ l198 (TYPE_2__*,int) ; 
 scalar_t__ l586 (TYPE_2__*,int) ; 

void cp_set_dir(e*a,int v){s*b=a->d;e*h;int c;{
if(!(a->f!=3&&a->f!=6))goto l661;{a->v=a->p;l157(a);return;}l661:;}{
if(!(a->l31))goto l659;v=a->p;l659:;}{if(!(!a->l34))goto l656;v=(a->p
==1)?(b->l30?0:1):a->p;l656:;}{if(!((a->d->k+2)->f==3))goto l647;v&=3
;goto l646;l647:;v&=1;l646:;}a->v=v;{h=b->k;l644:if(!(h<b->k+4))goto
l642;goto l641;l633:++h;goto l644;l641:{if(!((h->f==3||h->f==6)&&h!=a
&&h->v==a->v))goto l637;a->j&=~h->j;l637:;}goto l633;l642:;}{if(!(a->
l34))goto l634;{{if(!(b->l30))goto l629;{c=1;l630:if(!(c<32))goto l369
;goto l368;l733:++c;goto l630;l368:{if(!((a->j>>c&1)&&(l198(a,c)||
l586(a,c))))goto l737;a->j&=~(1<<c);l737:;}goto l733;l369:;}l629:;}
l157(a);}l634:;}cp_set_ts(a,a->j);}
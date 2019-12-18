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
struct TYPE_6__ {TYPE_3__* k; int /*<<< orphan*/  l30; } ;
typedef  TYPE_1__ s ;
struct TYPE_7__ {unsigned char* j; int* l40; } ;
typedef  TYPE_2__ l72 ;
struct TYPE_8__ {int f; size_t v; unsigned long j; size_t p; int /*<<< orphan*/  o; int /*<<< orphan*/  l46; int /*<<< orphan*/  l34; } ;
typedef  TYPE_3__ e ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static void l168(s*b){e
 *a;unsigned long j[4]={0,0,0,0},l159[2]={0,0};l72 o[4];int c;{if(!(!
b->l30||!b->k->l34))goto l474;return;l474:;}{a=b->k;l475:if(!(a<b->k+
4))goto l246;goto l486;l190:a++;goto l475;l486:{{if(!(a->f!=3&&a->f!=
6))goto l496;goto l190;l496:;}j[a->v]|=a->j;{if(!(!a->l46))goto l488;
j[a->p]|=(1<<16);l488:;}}goto l190;l246:;}l159[0]=~(j[0]|j[1]);l159[1
]=~(j[2]|j[3]);{c=1;l495:if(!(c<32))goto l491;goto l505;l503:c++;goto
l495;l505:{{if(!((l159[0]>>c)&1))goto l506;{o[0].j[c]=(unsigned char)c
;o[1].j[c]=(unsigned char)c;o[0].l40[c]=1;o[1].l40[c]=0;}goto l799;
l506:;{o[0].j[c]=0;o[1].j[c]=0;o[0].l40[c]=0;o[1].l40[c]=0;}l799:;}{
if(!((l159[1]>>c)&1))goto l501;{o[2].j[c]=(unsigned char)c;o[3].j[c]=
(unsigned char)c;o[2].l40[c]=3;o[3].l40[c]=2;}goto l502;l501:;{o[2].j
[c]=0;o[3].j[c]=0;o[2].l40[c]=0;o[3].l40[c]=0;}l502:;}}goto l503;l491
:;}memcpy(&b->k[0].o,o+0,sizeof(l72));memcpy(&b->k[1].o,o+1,sizeof(
l72));memcpy(&b->k[2].o,o+2,sizeof(l72));memcpy(&b->k[3].o,o+3,sizeof
(l72));}
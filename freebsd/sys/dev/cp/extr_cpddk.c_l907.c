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
struct TYPE_6__ {size_t l115; TYPE_2__* k; int /*<<< orphan*/ * l94; } ;
typedef  TYPE_1__ s ;
struct TYPE_7__ {int f; } ;
typedef  TYPE_2__ e ;

/* Variables and functions */
 int /*<<< orphan*/  l188 (TYPE_2__*) ; 
 int l90 (TYPE_2__*,int,int) ; 

__attribute__((used)) static void l907(s*b){unsigned long l91;
e*a;{l221:if(!((l91= * (volatile unsigned long* )&b->l94[b->l115])!=0
))goto l310;{ * (volatile unsigned long* )&b->l94[b->l115]=0;b->l115=
++b->l115%128;{if(!((l91&3489660928UL)!=3489660928UL))goto l309;{;
goto l221;}l309:;}{a=b->k;l307:if(!(a<b->k+4))goto l302;goto l299;
l306:++a;goto l307;l299:{if(!(a->f==3&&(l90(a,7,255)&16)))goto l298;{
;l188(a);}l298:;}goto l306;l302:;}}goto l221;l310:;}}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t l115; TYPE_2__* k; int /*<<< orphan*/ * l94; int /*<<< orphan*/  l563; } ;
typedef  TYPE_1__ s ;
struct TYPE_8__ {size_t l104; size_t l28; scalar_t__ l102; int /*<<< orphan*/ * l67; int /*<<< orphan*/ * l97; int /*<<< orphan*/  l70; } ;
typedef  TYPE_2__ e ;

/* Variables and functions */
 int /*<<< orphan*/  l268 (TYPE_2__*) ; 
 int /*<<< orphan*/  l820 (TYPE_2__*) ; 
 int /*<<< orphan*/  l907 (TYPE_1__*) ; 

void
cp_handle_interrupt(s*b){e*a;++b->l563;{if(!( * (volatile unsigned
long* )&b->l94[b->l115]))goto l292;l907(b);l292:;}{a=b->k;l291:if(!(a
<b->k+4))goto l284;goto l281;l286:++a;goto l291;l281:{{if(!(~(a->l70)))goto
l279;{{if(!( * (volatile unsigned long* )&a->l97[a->l104]))goto l277;
l268(a);l277:;}{if(!( * (volatile unsigned long* )&a->l67[a->l28]!= *
(volatile unsigned long* )((a)->l102)))goto l271;l820(a);l271:;}}l279
:;}}goto l286;l284:;}}
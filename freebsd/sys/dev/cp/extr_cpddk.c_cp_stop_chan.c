#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned long l35; int l36; scalar_t__* l75; unsigned long* l82; int /*<<< orphan*/  l70; TYPE_2__* d; scalar_t__ x; TYPE_1__* l42; int /*<<< orphan*/  f; } ;
typedef  TYPE_3__ e ;
struct TYPE_6__ {scalar_t__ g; } ;
struct TYPE_5__ {int /*<<< orphan*/  w; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

void
cp_stop_chan(e*a){unsigned long l175=0;unsigned long l96=0;int c;{if(
!(!a->f))goto l892;return;l892:;}outb(128,0);a->l35&=~2147483648UL; *
(volatile unsigned long* )((a)->x+8)=a->l35;{c=0;l893:if(!(c<200))goto
l913;goto l912;l446:c++;goto l893;l912:outb(128,0);goto l446;l913:;}{
if(!(a->l36&134217728))goto l584;{;a->l36&=~134217728; * (volatile
unsigned long* )((a)->x+16)=a->l36;l175|=4194304;l96|=65536;}l584:;}
outb(128,0);{if(!(( * (a)->l75)!=0))goto l653;{;{c=0;l911:if(!(c<4))goto
l354;goto l353;l290:++c;goto l911;l353: * (volatile unsigned long* )&
a->l42[c].w=2147483648UL|1073741824;goto l290;l354:;}l175|=2097152;
l96|=16777216;}l653:;}outb(128,0); * (volatile unsigned long* )((a)->
x+0)=l96;outb(128,0);( * (a)->l82)=l175;outb(128,0); * (volatile
unsigned long* )((a->d)->g+0)=513;outb(128,0);a->l70=~0;}
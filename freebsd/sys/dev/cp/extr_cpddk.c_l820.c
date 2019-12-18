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
struct TYPE_7__ {int l28; unsigned long* l67; int /*<<< orphan*/  (* l65 ) (TYPE_2__*,int) ;int /*<<< orphan*/  l200; TYPE_1__* l32; scalar_t__ l102; int /*<<< orphan*/  l635; } ;
typedef  TYPE_2__ e ;
struct TYPE_6__ {int /*<<< orphan*/  l88; int /*<<< orphan*/  t; } ;

/* Variables and functions */
 int /*<<< orphan*/  l575 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static void l820(e*a){int l205
=0;int l201=0;{if(!(!a->l32))goto l363;return;l363:;}++a->l635;{if(!(
 * (volatile unsigned long* )&a->l32[(a->l28+64-1)%64].t&1073741824))goto
l362;l205++;l362:;}{l360:if(!(( * (volatile unsigned long* )&a->l32[a
->l28].t&1073741824)&&( * (volatile unsigned long* )&a->l67[a->l28]!=
 * (volatile unsigned long* )((a)->l102))))goto l358;{l575(a);l201++;
}goto l360;l358:;}{if(!(l205))goto l356;{{if(!(l201<64-1))goto l355;{
{l350:if(!(( * (volatile unsigned long* )&a->l67[a->l28]!= * (
volatile unsigned long* )((a)->l102))))goto l349;{ * (volatile
unsigned long* )&a->l32[a->l28].t=0; * (volatile unsigned long* )&a->
l32[a->l28].l88=a->l67[a->l28]; * (volatile unsigned long* )&a->l32[(
a->l28+64-1)%64].l88=a->l67[a->l28];a->l28=++a->l28%64;}goto l350;
l349:;}}l355:;}++a->l200;{if(!(a->l65))goto l346;a->l65(a,5);l346:;}}
l356:;}}
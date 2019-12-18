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
struct TYPE_9__ {size_t l28; unsigned char** l136; int l571; unsigned long* l67; TYPE_1__* l32; int /*<<< orphan*/  (* l171 ) (TYPE_2__*,unsigned char*,int) ;int /*<<< orphan*/  l592; int /*<<< orphan*/  (* l65 ) (TYPE_2__*,int) ;int /*<<< orphan*/  l556; int /*<<< orphan*/  l52; int /*<<< orphan*/  l591; int /*<<< orphan*/  l200; } ;
typedef  TYPE_2__ e ;
struct TYPE_8__ {int /*<<< orphan*/  l88; int /*<<< orphan*/  t; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,unsigned char*,int) ; 

__attribute__((used)) static
void l575(e*a){int w=(( * (volatile unsigned long* )&a->l32[a->l28].t
)>>16&8191);unsigned char l127;{if(!(w>0))goto l424;l127=a->l136[a->
l28][--w];goto l852;l424:;l127=0;l852:;};{if(!(l127&64))goto l905;{++
a->l200;{if(!(a->l65))goto l881;a->l65(a,4);l881:;}}goto l875;l905:;{
if(!(!(l127&128)))goto l876;{++a->l591;{if(!(a->l65))goto l908;a->l65
(a,1);l908:;}}goto l438;l876:;{if(!(!a->l52&&!(l127&32)))goto l879;{
++a->l556;{if(!(a->l65))goto l450;a->l65(a,2);l450:;}}goto l903;l879:
;{a->l571+=w;++a->l592;{if(!(a->l171))goto l367;a->l171(a,a->l136[a->
l28],w);l367:;}}l903:;}l438:;}l875:;} * (volatile unsigned long* )&a
->l32[a->l28].t=0; * (volatile unsigned long* )&a->l32[a->l28].l88=a
->l67[a->l28]; * (volatile unsigned long* )&a->l32[(a->l28+64-1)%64].
l88=a->l67[a->l28];a->l28=++a->l28%64;}
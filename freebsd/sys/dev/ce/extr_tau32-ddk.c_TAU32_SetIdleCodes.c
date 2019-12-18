#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int SP4ZU; unsigned char** jyElQ3; int /*<<< orphan*/  h2LrH3; } ;
typedef  TYPE_1__ kWMzp1 ;

/* Variables and functions */
 int /*<<< orphan*/  GLE_s4 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  h2LrH3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uYS5N2 (int /*<<< orphan*/ *) ; 

int
__attribute__((cdecl))TAU32_SetIdleCodes(kWMzp1*J7Iki4,unsigned char*
PTDns3){int fRgzh2=0;int X3V8j4=(J7Iki4->SP4ZU==02)?32-0x1:32*02-1;{
J99ok3:{if(!(PTDns3[X3V8j4]>0xF&&PTDns3[X3V8j4]!=0xFF))goto bymxW4;
return 0;bymxW4:;}if(--X3V8j4>=0)goto J99ok3;};h2LrH3(&J7Iki4->h2LrH3
);X3V8j4=(J7Iki4->SP4ZU==0x2)?32-0x1:32*2-01;{lfF_u2:{if(!(PTDns3[
X3V8j4]<=0xF&&J7Iki4->jyElQ3[X3V8j4/32][X3V8j4%32]!=PTDns3[X3V8j4]))goto
rQ3tw3;{J7Iki4->jyElQ3[X3V8j4/32][X3V8j4%32]=PTDns3[X3V8j4];fRgzh2=01
;}rQ3tw3:;}if(--X3V8j4>=0)goto lfF_u2;};{if(!(fRgzh2))goto bY6sq;
GLE_s4(J7Iki4,(-1));bY6sq:;}uYS5N2(&J7Iki4->h2LrH3);return 0x1;}
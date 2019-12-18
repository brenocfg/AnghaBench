#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int p; int /*<<< orphan*/  d; int /*<<< orphan*/  l44; } ;
typedef  TYPE_1__ e ;

/* Variables and functions */
 int /*<<< orphan*/  l (int /*<<< orphan*/ ,int,unsigned char) ; 
 int /*<<< orphan*/  l176 (int /*<<< orphan*/ ,unsigned char,unsigned char) ; 
 int u (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char l603(e*a,unsigned char
z){unsigned char l27=16<<a->p;unsigned char r=0;int c;l(a->d,40,0);
l176(a->d,(z<<1)|1,l27);{c=0;l539:if(!(c<8))goto l537;goto l534;l532:
++c;goto l539;l534:{l(a->d,40,l27|8);{if(!(u(a->d,a->l44)&128))goto
l458;r|=1<<c;l458:;}l(a->d,40,l27);}goto l532;l537:;}l(a->d,40,0);
return r;}
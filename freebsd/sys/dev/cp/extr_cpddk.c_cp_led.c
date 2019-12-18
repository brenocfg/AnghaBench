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
struct TYPE_4__ {int l125; } ;
typedef  TYPE_1__ s ;

/* Variables and functions */
 int /*<<< orphan*/  l (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
cp_led(s*b,int m){{if(!(m))goto l868;b->l125|=16;goto l869;l868:;b->
l125&=~16;l869:;}l(b,0,b->l125);}
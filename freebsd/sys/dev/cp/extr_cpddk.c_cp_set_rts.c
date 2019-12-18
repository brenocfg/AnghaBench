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
struct TYPE_3__ {int l218; int l43; scalar_t__ x; } ;
typedef  TYPE_1__ e ;

/* Variables and functions */

void cp_set_rts(e*a,int m){a->l218=(m!=0);{if(!(a->
l218))goto l327;a->l43|=1048576;goto l324;l327:;a->l43&=~1048576;l324
:;} * (volatile unsigned long* )((a)->x+12)=a->l43;}
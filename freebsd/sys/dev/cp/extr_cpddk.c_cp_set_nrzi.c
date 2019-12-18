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
struct TYPE_3__ {int f; int l145; int l35; scalar_t__ x; } ;
typedef  TYPE_1__ e ;

/* Variables and functions */

void cp_set_nrzi(e*a,int m){{if(!(a->f!=1))goto l804;return;l804:;}a
->l145=m?1:0;{if(!(a->l145))goto l805;a->l35|=2097152;goto l402;l805:
;a->l35&=~2097152;l402:;} * (volatile unsigned long* )((a)->x+8)=a->
l35;}
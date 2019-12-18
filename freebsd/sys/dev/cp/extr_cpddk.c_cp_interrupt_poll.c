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
struct TYPE_3__ {scalar_t__ g; } ;
typedef  TYPE_1__ s ;

/* Variables and functions */

int cp_interrupt_poll(s*b,int l217){unsigned long l192= * (volatile
unsigned long* )((b)->g+4);;{if(!(!l192))goto l243;return 0;l243:;}{
if(!(l217))goto l825; * (volatile unsigned long* )((b)->g+4)=l192;
l825:;}return 1;}
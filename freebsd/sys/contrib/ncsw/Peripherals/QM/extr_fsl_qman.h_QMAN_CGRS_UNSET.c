#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* __state; } ;
struct qman_cgrs {TYPE_1__ q; } ;

/* Variables and functions */
 int __CGR_SHIFT (int) ; 
 size_t __CGR_WORD (int) ; 

__attribute__((used)) static __inline__ void QMAN_CGRS_UNSET(struct qman_cgrs *c, int num)
{
    c->q.__state[__CGR_WORD(num)] &= ~(0x80000000 >> __CGR_SHIFT(num));
}
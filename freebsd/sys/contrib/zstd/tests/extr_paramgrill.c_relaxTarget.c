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
struct TYPE_4__ {int cSpeed; int dSpeed; scalar_t__ cMem; } ;
typedef  TYPE_1__ constraint_t ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 int g_strictness ; 

__attribute__((used)) static constraint_t relaxTarget(constraint_t target) {
    target.cMem = (U32)-1;
    target.cSpeed = (target.cSpeed * g_strictness) / 100;
    target.dSpeed = (target.dSpeed * g_strictness) / 100;
    return target;
}
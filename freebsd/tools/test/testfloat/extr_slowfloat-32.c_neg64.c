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
struct TYPE_4__ {int /*<<< orphan*/  a0; int /*<<< orphan*/  a1; } ;
typedef  TYPE_1__ bits64X ;

/* Variables and functions */

__attribute__((used)) static bits64X neg64( bits64X a )
{

    if ( a.a1 == 0 ) {
        a.a0 = - a.a0;
    }
    else {
        a.a1 = - a.a1;
        a.a0 = ~ a.a0;
    }
    return a;

}
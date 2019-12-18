#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ a1; scalar_t__ a0; } ;
typedef  TYPE_1__ bits64X ;

/* Variables and functions */

__attribute__((used)) static bits64X add64( bits64X a, bits64X b )
{

    a.a1 += b.a1;
    a.a0 += b.a0 + ( a.a1 < b.a1 );
    return a;

}
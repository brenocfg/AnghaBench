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
struct TYPE_3__ {int d; size_t m; int y; } ;
typedef  TYPE_1__ date ;

/* Variables and functions */
 int* month1 ; 

__attribute__((used)) static int
ndaysji(date * idt)
{

	return (idt->d + month1[idt->m] + idt->y * 365 + idt->y / 4);
}
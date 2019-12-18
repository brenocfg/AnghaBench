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
struct TYPE_2__ {int addr; int eax; int ecx; int edx; scalar_t__ ctl; } ;

/* Variables and functions */
 TYPE_1__ v86 ; 
 int /*<<< orphan*/  v86int () ; 

void
delay(int period)
{
    v86.ctl = 0;
    v86.addr = 0x15;		/* int 0x15, function 0x86 */
    v86.eax = 0x8600;
    v86.ecx = period >> 16;
    v86.edx = period & 0xffff;
    v86int();
}
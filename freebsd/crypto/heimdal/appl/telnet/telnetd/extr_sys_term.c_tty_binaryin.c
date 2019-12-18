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
struct TYPE_2__ {int /*<<< orphan*/  c_iflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISTRIP ; 
 TYPE_1__ termbuf ; 

void
tty_binaryin(int on)
{
    if (on) {
	termbuf.c_iflag &= ~ISTRIP;
    } else {
	termbuf.c_iflag |= ISTRIP;
    }
}
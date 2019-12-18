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
struct source {int dummy; } ;
struct TYPE_2__ {struct source* readstack; scalar_t__ readsp; } ;

/* Variables and functions */
 TYPE_1__ bmachine ; 

void
reset_bmachine(struct source *src)
{

	bmachine.readsp = 0;
	bmachine.readstack[0] = *src;
}
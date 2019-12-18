#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int hz ; 

__attribute__((used)) static int
ms_to_ticks(int ms)
{
	if (hz > 1000)
		return ms*(hz/1000);

	return ms/(1000/hz);
}
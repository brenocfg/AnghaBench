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
 int /*<<< orphan*/  ioport_map (unsigned long,int) ; 
 int /*<<< orphan*/  iowrite16_rep (int /*<<< orphan*/ ,void const*,unsigned long) ; 

void outsw(unsigned long port, const void *src, unsigned long count)
{
	iowrite16_rep(ioport_map(port, 2), src, count);
}
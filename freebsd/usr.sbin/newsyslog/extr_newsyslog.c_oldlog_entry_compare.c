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
struct oldlog_entry {scalar_t__ t; } ;

/* Variables and functions */

__attribute__((used)) static int
oldlog_entry_compare(const void *a, const void *b)
{
	const struct oldlog_entry *ola = a, *olb = b;

	if (ola->t > olb->t)
		return (-1);
	else if (ola->t < olb->t)
		return (1);
	else
		return (0);
}
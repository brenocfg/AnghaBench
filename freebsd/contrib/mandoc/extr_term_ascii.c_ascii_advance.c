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
struct termp {int dummy; } ;

/* Variables and functions */
 size_t UINT16_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void
ascii_advance(struct termp *p, size_t len)
{
	size_t		i;

	assert(len < UINT16_MAX);
	for (i = 0; i < len; i++)
		putchar(' ');
}
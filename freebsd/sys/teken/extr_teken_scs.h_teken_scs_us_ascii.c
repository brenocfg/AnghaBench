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
typedef  int /*<<< orphan*/  teken_t ;
typedef  int /*<<< orphan*/  teken_char_t ;

/* Variables and functions */

__attribute__((used)) static teken_char_t
teken_scs_us_ascii(const teken_t *t, teken_char_t c)
{

	/* No processing. */
	(void)t;
	return (c);
}
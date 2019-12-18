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
typedef  int /*<<< orphan*/  uint8_t ;
struct cpack_state {int c_buf; size_t c_len; int /*<<< orphan*/ * c_next; } ;

/* Variables and functions */

int
cpack_uint8(struct cpack_state *cs, uint8_t *u)
{
	/* No space left? */
	if ((size_t)(cs->c_next - cs->c_buf) >= cs->c_len)
		return -1;

	*u = *cs->c_next;

	/* Move pointer past the uint8_t. */
	cs->c_next++;
	return 0;
}
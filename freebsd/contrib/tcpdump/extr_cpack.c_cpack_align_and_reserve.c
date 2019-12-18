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
struct cpack_state {int c_len; int /*<<< orphan*/  const* c_buf; int /*<<< orphan*/  c_next; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cpack_next_boundary (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 

const uint8_t *
cpack_align_and_reserve(struct cpack_state *cs, size_t wordsize)
{
	const uint8_t *next;

	/* Ensure alignment. */
	next = cpack_next_boundary(cs->c_buf, cs->c_next, wordsize);

	/* Too little space for wordsize bytes? */
	if (next - cs->c_buf + wordsize > cs->c_len)
		return NULL;

	return next;
}
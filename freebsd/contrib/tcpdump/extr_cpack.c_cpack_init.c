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
struct cpack_state {size_t c_len; int /*<<< orphan*/  const* c_buf; int /*<<< orphan*/  const* c_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct cpack_state*,int /*<<< orphan*/ ,int) ; 

int
cpack_init(struct cpack_state *cs, const uint8_t *buf, size_t buflen)
{
	memset(cs, 0, sizeof(*cs));

	cs->c_buf = buf;
	cs->c_len = buflen;
	cs->c_next = cs->c_buf;

	return 0;
}
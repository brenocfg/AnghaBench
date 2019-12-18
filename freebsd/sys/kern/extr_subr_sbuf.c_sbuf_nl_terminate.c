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
struct sbuf {int s_len; char* s_buf; scalar_t__ s_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBUF_ISDRAINATEOL (struct sbuf*) ; 
 int /*<<< orphan*/  assert_sbuf_integrity (struct sbuf*) ; 
 int /*<<< orphan*/  assert_sbuf_state (struct sbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_put_byte (struct sbuf*,char) ; 

int
sbuf_nl_terminate(struct sbuf *s)
{

	assert_sbuf_integrity(s);
	assert_sbuf_state(s, 0);

	/*
	 * If the s_buf isn't empty, the last byte is simply s_buf[s_len - 1].
	 *
	 * If the s_buf is empty because a drain function drained it, we
	 * remember if the last byte was a \n with the SBUF_DRAINATEOL flag in
	 * sbuf_drain().
	 *
	 * In either case, we only append a \n if the previous character was
	 * something else.
	 */
	if (s->s_len == 0) {
		if (!SBUF_ISDRAINATEOL(s))
			sbuf_put_byte(s, '\n');
	} else if (s->s_buf[s->s_len - 1] != '\n')
		sbuf_put_byte(s, '\n');

	if (s->s_error != 0)
		return (-1);
	return (0);
}
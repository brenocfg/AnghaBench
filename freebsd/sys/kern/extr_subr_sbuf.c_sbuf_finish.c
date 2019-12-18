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
struct sbuf {char* s_buf; size_t s_len; scalar_t__ s_error; int /*<<< orphan*/ * s_drain_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBUF_FINISHED ; 
 scalar_t__ SBUF_NULINCLUDED (struct sbuf*) ; 
 int /*<<< orphan*/  SBUF_SETFLAG (struct sbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_sbuf_integrity (struct sbuf*) ; 
 int /*<<< orphan*/  assert_sbuf_state (struct sbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ sbuf_drain (struct sbuf*) ; 

int
sbuf_finish(struct sbuf *s)
{

	assert_sbuf_integrity(s);
	assert_sbuf_state(s, 0);

	s->s_buf[s->s_len] = '\0';
	if (SBUF_NULINCLUDED(s))
		s->s_len++;
	if (s->s_drain_func != NULL) {
		while (s->s_len > 0 && s->s_error == 0)
			s->s_error = sbuf_drain(s);
	}
	SBUF_SETFLAG(s, SBUF_FINISHED);
#ifdef _KERNEL
	return (s->s_error);
#else
	if (s->s_error != 0) {
		errno = s->s_error;
		return (-1);
	}
	return (0);
#endif
}
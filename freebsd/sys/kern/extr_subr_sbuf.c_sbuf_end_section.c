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
struct sbuf {scalar_t__ s_sect_len; scalar_t__ s_error; scalar_t__ s_rec_off; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SBUF_CLEARFLAG (struct sbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBUF_INSECTION ; 
 int /*<<< orphan*/  SBUF_ISSECTION (struct sbuf*) ; 
 int /*<<< orphan*/  assert_sbuf_integrity (struct sbuf*) ; 
 int /*<<< orphan*/  assert_sbuf_state (struct sbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ roundup (scalar_t__,size_t) ; 
 int /*<<< orphan*/  sbuf_put_byte (struct sbuf*,int) ; 

ssize_t
sbuf_end_section(struct sbuf *s, ssize_t old_len, size_t pad, int c)
{
	ssize_t len;

	assert_sbuf_integrity(s);
	assert_sbuf_state(s, 0);
	KASSERT(SBUF_ISSECTION(s),
	    ("attempt to end a section when not in a section"));

	if (pad > 1) {
		len = roundup(s->s_sect_len, pad) - s->s_sect_len;
		for (; s->s_error == 0 && len > 0; len--)
			sbuf_put_byte(s, c);
	}
	len = s->s_sect_len;
	if (old_len == -1) {
		s->s_rec_off = s->s_sect_len = 0;
		SBUF_CLEARFLAG(s, SBUF_INSECTION);
	} else {
		s->s_sect_len += old_len;
	}
	if (s->s_error != 0)
		return (-1);
	return (len);
}
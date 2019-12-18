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
struct sbuf {scalar_t__ s_sect_len; int /*<<< orphan*/  s_len; int /*<<< orphan*/  s_rec_off; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SBUF_INSECTION ; 
 int /*<<< orphan*/  SBUF_ISSECTION (struct sbuf*) ; 
 int /*<<< orphan*/  SBUF_SETFLAG (struct sbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_sbuf_integrity (struct sbuf*) ; 
 int /*<<< orphan*/  assert_sbuf_state (struct sbuf*,int /*<<< orphan*/ ) ; 

void
sbuf_start_section(struct sbuf *s, ssize_t *old_lenp)
{

	assert_sbuf_integrity(s);
	assert_sbuf_state(s, 0);

	if (!SBUF_ISSECTION(s)) {
		KASSERT(s->s_sect_len == 0,
		    ("s_sect_len != 0 when starting a section"));
		if (old_lenp != NULL)
			*old_lenp = -1;
		s->s_rec_off = s->s_len;
		SBUF_SETFLAG(s, SBUF_INSECTION);
	} else {
		KASSERT(old_lenp != NULL,
		    ("s_sect_len should be saved when starting a subsection"));
		*old_lenp = s->s_sect_len;
		s->s_sect_len = 0;
	}
}
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
typedef  int /*<<< orphan*/  u_char ;
struct uni_msg {int /*<<< orphan*/ * b_buf; int /*<<< orphan*/ * b_lim; int /*<<< orphan*/ * b_rptr; int /*<<< orphan*/ * b_wptr; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ EXTRA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_UNIMSG ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 
 size_t uni_msg_leading (struct uni_msg*) ; 
 size_t uni_msg_len (struct uni_msg*) ; 

int
uni_msg_extend(struct uni_msg *m, size_t s)
{
	u_char *b;
	size_t len, lead;

	lead = uni_msg_leading(m);
	len = uni_msg_len(m);
	s += lead + len + EXTRA;
	if ((b = malloc(s, M_UNIMSG, M_NOWAIT)) == NULL) {
		uni_msg_destroy(m);
		return (ENOMEM);
	}

	bcopy(m->b_rptr, b + lead, len);
	free(m->b_buf, M_UNIMSG);

	m->b_buf = b;
	m->b_rptr = m->b_buf + lead;
	m->b_wptr = m->b_rptr + len;
	m->b_lim = m->b_buf + s;

	return (0);
}
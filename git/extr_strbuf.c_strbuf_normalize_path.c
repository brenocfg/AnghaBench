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
struct strbuf {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ normalize_path_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_swap (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

int strbuf_normalize_path(struct strbuf *src)
{
	struct strbuf dst = STRBUF_INIT;

	strbuf_grow(&dst, src->len);
	if (normalize_path_copy(dst.buf, src->buf) < 0) {
		strbuf_release(&dst);
		return -1;
	}

	/*
	 * normalize_path does not tell us the new length, so we have to
	 * compute it by looking for the new NUL it placed
	 */
	strbuf_setlen(&dst, strlen(dst.buf));
	strbuf_swap(src, &dst);
	strbuf_release(&dst);
	return 0;
}
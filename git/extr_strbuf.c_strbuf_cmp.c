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
struct strbuf {size_t len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

int strbuf_cmp(const struct strbuf *a, const struct strbuf *b)
{
	size_t len = a->len < b->len ? a->len: b->len;
	int cmp = memcmp(a->buf, b->buf, len);
	if (cmp)
		return cmp;
	return a->len < b->len ? -1: a->len != b->len;
}
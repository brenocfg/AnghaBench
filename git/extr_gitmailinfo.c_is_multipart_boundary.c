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
struct strbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct mailinfo {struct strbuf** content_top; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int is_multipart_boundary(struct mailinfo *mi, const struct strbuf *line)
{
	struct strbuf *content_top = *(mi->content_top);

	return ((content_top->len <= line->len) &&
		!memcmp(line->buf, content_top->buf, content_top->len));
}
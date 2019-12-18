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
struct strbuf {size_t len; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 scalar_t__ is_dir_sep (int /*<<< orphan*/ ) ; 
 size_t offset_1st_component (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 

__attribute__((used)) static void strip_last_component(struct strbuf *path)
{
	size_t offset = offset_1st_component(path->buf);
	size_t len = path->len;

	/* Find start of the last component */
	while (offset < len && !is_dir_sep(path->buf[len - 1]))
		len--;
	/* Skip sequences of multiple path-separators */
	while (offset < len && is_dir_sep(path->buf[len - 1]))
		len--;

	strbuf_setlen(path, len);
}
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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct ref_format {int dummy; } ;
struct ref_array_item {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ format_ref_array_item (struct ref_array_item*,struct ref_format const*,struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

void show_ref_array_item(struct ref_array_item *info,
			 const struct ref_format *format)
{
	struct strbuf final_buf = STRBUF_INIT;
	struct strbuf error_buf = STRBUF_INIT;

	if (format_ref_array_item(info, format, &final_buf, &error_buf))
		die("%s", error_buf.buf);
	fwrite(final_buf.buf, 1, final_buf.len, stdout);
	strbuf_release(&error_buf);
	strbuf_release(&final_buf);
	putchar('\n');
}
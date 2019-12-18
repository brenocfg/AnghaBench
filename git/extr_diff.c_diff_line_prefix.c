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
struct strbuf {char const* buf; } ;
struct diff_options {int /*<<< orphan*/  output_prefix_data; struct strbuf* (* output_prefix ) (struct diff_options*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct strbuf* stub1 (struct diff_options*,int /*<<< orphan*/ ) ; 

const char *diff_line_prefix(struct diff_options *opt)
{
	struct strbuf *msgbuf;
	if (!opt->output_prefix)
		return "";

	msgbuf = opt->output_prefix(opt, opt->output_prefix_data);
	return msgbuf->buf;
}
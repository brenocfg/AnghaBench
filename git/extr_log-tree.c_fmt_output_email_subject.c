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
struct strbuf {int dummy; } ;
struct rev_info {scalar_t__ total; scalar_t__* subject_prefix; int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  digits_in_number (scalar_t__) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,scalar_t__*,...) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 

void fmt_output_email_subject(struct strbuf *sb, struct rev_info *opt)
{
	if (opt->total > 0) {
		strbuf_addf(sb, "Subject: [%s%s%0*d/%d] ",
			    opt->subject_prefix,
			    *opt->subject_prefix ? " " : "",
			    digits_in_number(opt->total),
			    opt->nr, opt->total);
	} else if (opt->total == 0 && opt->subject_prefix && *opt->subject_prefix) {
		strbuf_addf(sb, "Subject: [%s] ",
			    opt->subject_prefix);
	} else {
		strbuf_addstr(sb, "Subject: ");
	}
}
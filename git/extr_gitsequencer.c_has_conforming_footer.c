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
struct trailer_info {scalar_t__ trailer_start; scalar_t__ trailer_end; size_t trailer_nr; int /*<<< orphan*/ * trailers; } ;
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct process_trailer_options {int no_divider; } ;

/* Variables and functions */
 struct process_trailer_options PROCESS_TRAILER_OPTIONS_INIT ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trailer_info_get (struct trailer_info*,int /*<<< orphan*/ ,struct process_trailer_options*) ; 
 int /*<<< orphan*/  trailer_info_release (struct trailer_info*) ; 

__attribute__((used)) static int has_conforming_footer(struct strbuf *sb, struct strbuf *sob,
	size_t ignore_footer)
{
	struct process_trailer_options opts = PROCESS_TRAILER_OPTIONS_INIT;
	struct trailer_info info;
	size_t i;
	int found_sob = 0, found_sob_last = 0;

	opts.no_divider = 1;

	trailer_info_get(&info, sb->buf, &opts);

	if (info.trailer_start == info.trailer_end)
		return 0;

	for (i = 0; i < info.trailer_nr; i++)
		if (sob && !strncmp(info.trailers[i], sob->buf, sob->len)) {
			found_sob = 1;
			if (i == info.trailer_nr - 1)
				found_sob_last = 1;
		}

	trailer_info_release(&info);

	if (found_sob_last)
		return 3;
	if (found_sob)
		return 2;
	return 1;
}
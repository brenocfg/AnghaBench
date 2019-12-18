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
struct trailer_info {int dummy; } ;
struct strbuf {int dummy; } ;
struct process_trailer_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  format_trailer_info (struct strbuf*,struct trailer_info*,struct process_trailer_options const*) ; 
 int /*<<< orphan*/  trailer_info_get (struct trailer_info*,char const*,struct process_trailer_options const*) ; 
 int /*<<< orphan*/  trailer_info_release (struct trailer_info*) ; 

void format_trailers_from_commit(struct strbuf *out, const char *msg,
				 const struct process_trailer_options *opts)
{
	struct trailer_info info;

	trailer_info_get(&info, msg, opts);
	format_trailer_info(out, &info, opts);
	trailer_info_release(&info);
}
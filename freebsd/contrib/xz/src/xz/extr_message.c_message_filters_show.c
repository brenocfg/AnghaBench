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
typedef  int /*<<< orphan*/  lzma_filter ;
typedef  enum message_verbosity { ____Placeholder_message_verbosity } message_verbosity ;

/* Variables and functions */
 int FILTERS_STR_SIZE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  message_filters_to_str (char*,int /*<<< orphan*/  const*,int) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

extern void
message_filters_show(enum message_verbosity v, const lzma_filter *filters)
{
	if (v > verbosity)
		return;

	char buf[FILTERS_STR_SIZE];
	message_filters_to_str(buf, filters, true);
	fprintf(stderr, _("%s: Filter chain: %s\n"), progname, buf);
	return;
}
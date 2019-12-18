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
struct lafe_line_reader {char* line_end; scalar_t__ nullSeparator; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcspn (char*,char*) ; 

__attribute__((used)) static void
lafe_line_reader_find_eol(struct lafe_line_reader *lr)
{

	lr->line_end += strcspn(lr->line_end,
	    lr->nullSeparator ? "" : "\x0d\x0a");
	*lr->line_end = '\0'; /* Noop if line_end == buff_end */
}
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
struct fragment {int /*<<< orphan*/  newlines; int /*<<< orphan*/  newpos; int /*<<< orphan*/  oldlines; int /*<<< orphan*/  oldpos; } ;

/* Variables and functions */
 int parse_range (char const*,int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_fragment_header(const char *line, int len, struct fragment *fragment)
{
	int offset;

	if (!len || line[len-1] != '\n')
		return -1;

	/* Figure out the number of lines in a fragment */
	offset = parse_range(line, len, 4, " +", &fragment->oldpos, &fragment->oldlines);
	offset = parse_range(line, len, offset, " @@", &fragment->newpos, &fragment->newlines);

	return offset;
}
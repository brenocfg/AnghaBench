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
struct fragment {int oldlines; int newlines; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int linelen (char const*,int) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 
 int /*<<< orphan*/  warning (char*,...) ; 

__attribute__((used)) static void recount_diff(const char *line, int size, struct fragment *fragment)
{
	int oldlines = 0, newlines = 0, ret = 0;

	if (size < 1) {
		warning("recount: ignore empty hunk");
		return;
	}

	for (;;) {
		int len = linelen(line, size);
		size -= len;
		line += len;

		if (size < 1)
			break;

		switch (*line) {
		case ' ': case '\n':
			newlines++;
			/* fall through */
		case '-':
			oldlines++;
			continue;
		case '+':
			newlines++;
			continue;
		case '\\':
			continue;
		case '@':
			ret = size < 3 || !starts_with(line, "@@ ");
			break;
		case 'd':
			ret = size < 5 || !starts_with(line, "diff ");
			break;
		default:
			ret = -1;
			break;
		}
		if (ret) {
			warning(_("recount: unexpected line: %.*s"),
				(int)linelen(line, size), line);
			return;
		}
		break;
	}
	fragment->oldlines = oldlines;
	fragment->newlines = newlines;
}
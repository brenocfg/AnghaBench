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
struct mtree_option {int dummy; } ;
struct archive_read {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int add_option (struct archive_read*,struct mtree_option**,char const*,int) ; 
 int /*<<< orphan*/  remove_option (struct mtree_option**,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 int strcspn (char const*,char*) ; 
 int strspn (char const*,char*) ; 

__attribute__((used)) static int
process_global_set(struct archive_read *a,
    struct mtree_option **global, const char *line)
{
	const char *next, *eq;
	size_t len;
	int r;

	line += 4;
	for (;;) {
		next = line + strspn(line, " \t\r\n");
		if (*next == '\0')
			return (ARCHIVE_OK);
		line = next;
		next = line + strcspn(line, " \t\r\n");
		eq = strchr(line, '=');
		if (eq > next)
			len = next - line;
		else
			len = eq - line;

		remove_option(global, line, len);
		r = add_option(a, global, line, next - line);
		if (r != ARCHIVE_OK)
			return (r);
		line = next;
	}
}
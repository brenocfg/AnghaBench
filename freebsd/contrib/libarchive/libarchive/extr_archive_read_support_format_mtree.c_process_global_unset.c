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
struct archive_read {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_options (struct mtree_option*) ; 
 int /*<<< orphan*/  remove_option (struct mtree_option**,char const*,size_t) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 size_t strcspn (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int strspn (char const*,char*) ; 

__attribute__((used)) static int
process_global_unset(struct archive_read *a,
    struct mtree_option **global, const char *line)
{
	const char *next;
	size_t len;

	line += 6;
	if (strchr(line, '=') != NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "/unset shall not contain `='");
		return ARCHIVE_FATAL;
	}

	for (;;) {
		next = line + strspn(line, " \t\r\n");
		if (*next == '\0')
			return (ARCHIVE_OK);
		line = next;
		len = strcspn(line, " \t\r\n");

		if (len == 3 && strncmp(line, "all", 3) == 0) {
			free_options(*global);
			*global = NULL;
		} else {
			remove_option(global, line, len);
		}

		line += len;
	}
}
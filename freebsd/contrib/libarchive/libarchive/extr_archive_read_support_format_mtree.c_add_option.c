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
struct mtree_option {char* value; struct mtree_option* next; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct mtree_option*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static int
add_option(struct archive_read *a, struct mtree_option **global,
    const char *value, size_t len)
{
	struct mtree_option *opt;

	if ((opt = malloc(sizeof(*opt))) == NULL) {
		archive_set_error(&a->archive, errno, "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}
	if ((opt->value = malloc(len + 1)) == NULL) {
		free(opt);
		archive_set_error(&a->archive, errno, "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}
	memcpy(opt->value, value, len);
	opt->value[len] = '\0';
	opt->next = *global;
	*global = opt;
	return (ARCHIVE_OK);
}
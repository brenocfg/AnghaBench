#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* replace_email; struct TYPE_8__* replace_name; struct TYPE_8__* real_email; struct TYPE_8__* real_name; } ;
typedef  TYPE_1__ git_mailmap_entry ;
struct TYPE_9__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_2__ git_mailmap ;

/* Variables and functions */
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int GIT_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* git__calloc (int,int) ; 
 void* git__substrdup (char const*,size_t) ; 
 int git_vector_insert_sorted (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mailmap_entry_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mailmap_entry_replace ; 

__attribute__((used)) static int mailmap_add_entry_unterminated(
	git_mailmap *mm,
	const char *real_name, size_t real_name_size,
	const char *real_email, size_t real_email_size,
	const char *replace_name, size_t replace_name_size,
	const char *replace_email, size_t replace_email_size)
{
	int error;
	git_mailmap_entry *entry = git__calloc(1, sizeof(git_mailmap_entry));
	GIT_ERROR_CHECK_ALLOC(entry);

	assert(mm && replace_email && *replace_email);

	if (real_name_size > 0) {
		entry->real_name = git__substrdup(real_name, real_name_size);
		GIT_ERROR_CHECK_ALLOC(entry->real_name);
	}
	if (real_email_size > 0) {
		entry->real_email = git__substrdup(real_email, real_email_size);
		GIT_ERROR_CHECK_ALLOC(entry->real_email);
	}
	if (replace_name_size > 0) {
		entry->replace_name = git__substrdup(replace_name, replace_name_size);
		GIT_ERROR_CHECK_ALLOC(entry->replace_name);
	}
	entry->replace_email = git__substrdup(replace_email, replace_email_size);
	GIT_ERROR_CHECK_ALLOC(entry->replace_email);

	error = git_vector_insert_sorted(&mm->entries, entry, mailmap_entry_replace);
	if (error == GIT_EEXISTS)
		error = GIT_OK;
	else if (error < 0)
		mailmap_entry_free(entry);

	return error;
}
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
struct CLEANABLE_FILE {int /*<<< orphan*/  fn; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct CLEANABLE_FILE*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  files ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 struct CLEANABLE_FILE* sort_malloc (int) ; 
 int /*<<< orphan*/  sort_strdup (char const*) ; 
 int /*<<< orphan*/  tmp_files ; 
 int /*<<< orphan*/  tmp_files_sem ; 

void
tmp_file_atexit(const char *tmp_file)
{

	if (tmp_file) {
		sem_wait(&tmp_files_sem);
		struct CLEANABLE_FILE *item =
		    sort_malloc(sizeof(struct CLEANABLE_FILE));
		item->fn = sort_strdup(tmp_file);
		LIST_INSERT_HEAD(&tmp_files, item, files);
		sem_post(&tmp_files_sem);
	}
}
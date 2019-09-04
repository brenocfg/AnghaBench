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
struct index_state {int dummy; } ;
struct dir_struct {scalar_t__ nr; struct dir_entry** entries; int /*<<< orphan*/  alloc; } ;
struct dir_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct dir_entry**,scalar_t__,int /*<<< orphan*/ ) ; 
 struct dir_entry* dir_entry_new (char const*,int) ; 
 int /*<<< orphan*/  ignore_case ; 
 scalar_t__ index_file_exists (struct index_state*,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dir_entry *dir_add_name(struct dir_struct *dir,
				      struct index_state *istate,
				      const char *pathname, int len)
{
	if (index_file_exists(istate, pathname, len, ignore_case))
		return NULL;

	ALLOC_GROW(dir->entries, dir->nr+1, dir->alloc);
	return dir->entries[dir->nr++] = dir_entry_new(pathname, len);
}
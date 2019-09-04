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
struct dir_struct {scalar_t__ ignored_nr; struct dir_entry** ignored; int /*<<< orphan*/  ignored_alloc; } ;
struct dir_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct dir_entry**,scalar_t__,int /*<<< orphan*/ ) ; 
 struct dir_entry* dir_entry_new (char const*,int) ; 
 int /*<<< orphan*/  index_name_is_other (struct index_state*,char const*,int) ; 

struct dir_entry *dir_add_ignored(struct dir_struct *dir,
				  struct index_state *istate,
				  const char *pathname, int len)
{
	if (!index_name_is_other(istate, pathname, len))
		return NULL;

	ALLOC_GROW(dir->ignored, dir->ignored_nr+1, dir->ignored_alloc);
	return dir->ignored[dir->ignored_nr++] = dir_entry_new(pathname, len);
}
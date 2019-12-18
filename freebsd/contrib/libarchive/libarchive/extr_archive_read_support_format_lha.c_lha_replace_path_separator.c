#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int* s; } ;
struct lha {TYPE_1__ ws; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_entry_copy_pathname_w (struct archive_entry*,int*) ; 
 int /*<<< orphan*/  archive_entry_copy_symlink_w (struct archive_entry*,int*) ; 
 int /*<<< orphan*/ * archive_entry_pathname_w (struct archive_entry*) ; 
 int /*<<< orphan*/ * archive_entry_symlink_w (struct archive_entry*) ; 
 size_t archive_strlen (TYPE_1__*) ; 
 int /*<<< orphan*/  archive_wstrcpy (TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
lha_replace_path_separator(struct lha *lha, struct archive_entry *entry)
{
	const wchar_t *wp;
	size_t i;

	if ((wp = archive_entry_pathname_w(entry)) != NULL) {
		archive_wstrcpy(&(lha->ws), wp);
		for (i = 0; i < archive_strlen(&(lha->ws)); i++) {
			if (lha->ws.s[i] == L'\\')
				lha->ws.s[i] = L'/';
		}
		archive_entry_copy_pathname_w(entry, lha->ws.s);
	}

	if ((wp = archive_entry_symlink_w(entry)) != NULL) {
		archive_wstrcpy(&(lha->ws), wp);
		for (i = 0; i < archive_strlen(&(lha->ws)); i++) {
			if (lha->ws.s[i] == L'\\')
				lha->ws.s[i] = L'/';
		}
		archive_entry_copy_symlink_w(entry, lha->ws.s);
	}
}
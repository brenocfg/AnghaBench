#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct atom_value {void* s; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 void* copy_email (char const*) ; 
 void* copy_line (char const*) ; 
 void* copy_name (char const*) ; 
 char* find_wholine (char const*,int,void*) ; 
 int /*<<< orphan*/  grab_date (char const*,struct atom_value*,char const*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 TYPE_1__* used_atom ; 
 int used_atom_cnt ; 

__attribute__((used)) static void grab_person(const char *who, struct atom_value *val, int deref, void *buf)
{
	int i;
	int wholen = strlen(who);
	const char *wholine = NULL;

	for (i = 0; i < used_atom_cnt; i++) {
		const char *name = used_atom[i].name;
		struct atom_value *v = &val[i];
		if (!!deref != (*name == '*'))
			continue;
		if (deref)
			name++;
		if (strncmp(who, name, wholen))
			continue;
		if (name[wholen] != 0 &&
		    strcmp(name + wholen, "name") &&
		    strcmp(name + wholen, "email") &&
		    !starts_with(name + wholen, "date"))
			continue;
		if (!wholine)
			wholine = find_wholine(who, wholen, buf);
		if (!wholine)
			return; /* no point looking for it */
		if (name[wholen] == 0)
			v->s = copy_line(wholine);
		else if (!strcmp(name + wholen, "name"))
			v->s = copy_name(wholine);
		else if (!strcmp(name + wholen, "email"))
			v->s = copy_email(wholine);
		else if (starts_with(name + wholen, "date"))
			grab_date(wholine, v, name);
	}

	/*
	 * For a tag or a commit object, if "creator" or "creatordate" is
	 * requested, do something special.
	 */
	if (strcmp(who, "tagger") && strcmp(who, "committer"))
		return; /* "author" for commit object is not wanted */
	if (!wholine)
		wholine = find_wholine(who, wholen, buf);
	if (!wholine)
		return;
	for (i = 0; i < used_atom_cnt; i++) {
		const char *name = used_atom[i].name;
		struct atom_value *v = &val[i];
		if (!!deref != (*name == '*'))
			continue;
		if (deref)
			name++;

		if (starts_with(name, "creatordate"))
			grab_date(wholine, v, name);
		else if (!strcmp(name, "creator"))
			v->s = copy_line(wholine);
	}
}
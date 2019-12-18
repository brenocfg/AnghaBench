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
struct pt_mapped_section {int dummy; } ;
struct pt_section_list {struct pt_section_list* next; struct pt_mapped_section section; } ;
struct pt_section {int dummy; } ;
struct pt_image {struct pt_section_list* sections; } ;
struct pt_asid {int dummy; } ;

/* Variables and functions */
 int pt_asid_from_user (struct pt_asid*,struct pt_asid const*) ; 
 int pt_asid_match (struct pt_asid const*,struct pt_asid*) ; 
 struct pt_asid* pt_msec_asid (struct pt_mapped_section*) ; 
 struct pt_section* pt_msec_section (struct pt_mapped_section*) ; 
 char* pt_section_filename (struct pt_section const*) ; 
 int /*<<< orphan*/  pt_section_list_free (struct pt_section_list*) ; 
 int pte_invalid ; 
 scalar_t__ strcmp (char const*,char const*) ; 

int pt_image_remove_by_filename(struct pt_image *image, const char *filename,
				const struct pt_asid *uasid)
{
	struct pt_section_list **list;
	struct pt_asid asid;
	int errcode, removed;

	if (!image || !filename)
		return -pte_invalid;

	errcode = pt_asid_from_user(&asid, uasid);
	if (errcode < 0)
		return errcode;

	removed = 0;
	for (list = &image->sections; *list;) {
		struct pt_mapped_section *msec;
		const struct pt_section *sec;
		const struct pt_asid *masid;
		struct pt_section_list *trash;
		const char *tname;

		trash = *list;
		msec = &trash->section;
		masid = pt_msec_asid(msec);

		errcode = pt_asid_match(masid, &asid);
		if (errcode < 0)
			return errcode;

		if (!errcode) {
			list = &trash->next;
			continue;
		}

		sec = pt_msec_section(msec);
		tname = pt_section_filename(sec);

		if (tname && (strcmp(tname, filename) == 0)) {
			*list = trash->next;
			pt_section_list_free(trash);

			removed += 1;
		} else
			list = &trash->next;
	}

	return removed;
}
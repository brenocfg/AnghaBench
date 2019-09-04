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
struct string_list_item {struct resolve_undo_info* util; } ;
struct string_list {int strdup_strings; } ;
struct resolve_undo_info {int /*<<< orphan*/ * oid; int /*<<< orphan*/ * mode; } ;
struct TYPE_2__ {unsigned int rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  oidread (int /*<<< orphan*/ *,unsigned char const*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int) ; 
 struct string_list_item* string_list_insert (struct string_list*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strtoul (char const*,char**,int) ; 
 TYPE_1__* the_hash_algo ; 
 void* xcalloc (int,int) ; 

struct string_list *resolve_undo_read(const char *data, unsigned long size)
{
	struct string_list *resolve_undo;
	size_t len;
	char *endptr;
	int i;
	const unsigned rawsz = the_hash_algo->rawsz;

	resolve_undo = xcalloc(1, sizeof(*resolve_undo));
	resolve_undo->strdup_strings = 1;

	while (size) {
		struct string_list_item *lost;
		struct resolve_undo_info *ui;

		len = strlen(data) + 1;
		if (size <= len)
			goto error;
		lost = string_list_insert(resolve_undo, data);
		if (!lost->util)
			lost->util = xcalloc(1, sizeof(*ui));
		ui = lost->util;
		size -= len;
		data += len;

		for (i = 0; i < 3; i++) {
			ui->mode[i] = strtoul(data, &endptr, 8);
			if (!endptr || endptr == data || *endptr)
				goto error;
			len = (endptr + 1) - (char*)data;
			if (size <= len)
				goto error;
			size -= len;
			data += len;
		}

		for (i = 0; i < 3; i++) {
			if (!ui->mode[i])
				continue;
			if (size < rawsz)
				goto error;
			oidread(&ui->oid[i], (const unsigned char *)data);
			size -= rawsz;
			data += rawsz;
		}
	}
	return resolve_undo;

error:
	string_list_clear(resolve_undo, 1);
	error("Index records invalid resolve-undo information");
	return NULL;
}
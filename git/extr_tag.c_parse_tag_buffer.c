#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  type ;
struct TYPE_3__ {int parsed; } ;
struct tag {int /*<<< orphan*/  date; int /*<<< orphan*/  tag; struct object* tagged; TYPE_1__ object; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct object {int dummy; } ;
struct TYPE_4__ {int hexsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  blob_type ; 
 int /*<<< orphan*/  commit_type ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 scalar_t__ lookup_blob (struct repository*,struct object_id*) ; 
 scalar_t__ lookup_commit (struct repository*,struct object_id*) ; 
 scalar_t__ lookup_tag (struct repository*,struct object_id*) ; 
 scalar_t__ lookup_tree (struct repository*,struct object_id*) ; 
 char* memchr (char const*,char,int) ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ parse_oid_hex (char const*,struct object_id*,char const**) ; 
 int /*<<< orphan*/  parse_tag_date (char const*,char const*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tag_type ; 
 TYPE_2__* the_hash_algo ; 
 int /*<<< orphan*/  tree_type ; 
 int /*<<< orphan*/  xmemdupz (char const*,int) ; 

int parse_tag_buffer(struct repository *r, struct tag *item, const void *data, unsigned long size)
{
	struct object_id oid;
	char type[20];
	const char *bufptr = data;
	const char *tail = bufptr + size;
	const char *nl;

	if (item->object.parsed)
		return 0;
	item->object.parsed = 1;

	if (size < the_hash_algo->hexsz + 24)
		return -1;
	if (memcmp("object ", bufptr, 7) || parse_oid_hex(bufptr + 7, &oid, &bufptr) || *bufptr++ != '\n')
		return -1;

	if (!starts_with(bufptr, "type "))
		return -1;
	bufptr += 5;
	nl = memchr(bufptr, '\n', tail - bufptr);
	if (!nl || sizeof(type) <= (nl - bufptr))
		return -1;
	memcpy(type, bufptr, nl - bufptr);
	type[nl - bufptr] = '\0';
	bufptr = nl + 1;

	if (!strcmp(type, blob_type)) {
		item->tagged = (struct object *)lookup_blob(r, &oid);
	} else if (!strcmp(type, tree_type)) {
		item->tagged = (struct object *)lookup_tree(r, &oid);
	} else if (!strcmp(type, commit_type)) {
		item->tagged = (struct object *)lookup_commit(r, &oid);
	} else if (!strcmp(type, tag_type)) {
		item->tagged = (struct object *)lookup_tag(r, &oid);
	} else {
		error("Unknown type %s", type);
		item->tagged = NULL;
	}

	if (bufptr + 4 < tail && starts_with(bufptr, "tag "))
		; 		/* good */
	else
		return -1;
	bufptr += 4;
	nl = memchr(bufptr, '\n', tail - bufptr);
	if (!nl)
		return -1;
	item->tag = xmemdupz(bufptr, nl - bufptr);
	bufptr = nl + 1;

	if (bufptr + 7 < tail && starts_with(bufptr, "tagger "))
		item->date = parse_tag_date(bufptr, tail);
	else
		item->date = 0;

	return 0;
}
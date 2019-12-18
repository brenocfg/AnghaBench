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
typedef  void* wchar_t ;
struct archive_acl_entry {int type; scalar_t__ tag; int id; int permset; int /*<<< orphan*/  name; struct archive_acl_entry* next; } ;
struct archive_acl {int mode; struct archive_acl_entry* acl_head; } ;
struct archive {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ ARCHIVE_ENTRY_ACL_GROUP_OBJ ; 
 scalar_t__ ARCHIVE_ENTRY_ACL_OTHER ; 
 int ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID ; 
 int ARCHIVE_ENTRY_ACL_STYLE_MARK_DEFAULT ; 
 int ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA ; 
 int ARCHIVE_ENTRY_ACL_TYPE_ACCESS ; 
 int ARCHIVE_ENTRY_ACL_TYPE_DEFAULT ; 
 int ARCHIVE_ENTRY_ACL_TYPE_POSIX1E ; 
 scalar_t__ ARCHIVE_ENTRY_ACL_USER_OBJ ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  __archive_errx (int,char*) ; 
 int /*<<< orphan*/  append_entry_w (void***,void* const*,int,scalar_t__,int,void* const*,int,int) ; 
 int archive_acl_text_len (struct archive_acl*,int,int,int,struct archive*,int /*<<< orphan*/ *) ; 
 int archive_acl_text_want_type (struct archive_acl*,int) ; 
 int archive_mstring_get_wcs (struct archive*,int /*<<< orphan*/ *,void* const**) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (void**) ; 
 scalar_t__ malloc (int) ; 
 size_t wcslen (void**) ; 

wchar_t *
archive_acl_to_text_w(struct archive_acl *acl, ssize_t *text_len, int flags,
    struct archive *a)
{
	int count;
	ssize_t length;
	size_t len;
	const wchar_t *wname;
	const wchar_t *prefix;
	wchar_t separator;
	struct archive_acl_entry *ap;
	int id, r, want_type;
	wchar_t *wp, *ws;

	want_type = archive_acl_text_want_type(acl, flags);

	/* Both NFSv4 and POSIX.1 types found */
	if (want_type == 0)
		return (NULL);

	if (want_type == ARCHIVE_ENTRY_ACL_TYPE_POSIX1E)
		flags |= ARCHIVE_ENTRY_ACL_STYLE_MARK_DEFAULT;

	length = archive_acl_text_len(acl, want_type, flags, 1, a, NULL);

	if (length == 0)
		return (NULL);

	if (flags & ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA)
		separator = L',';
	else
		separator = L'\n';

	/* Now, allocate the string and actually populate it. */
	wp = ws = (wchar_t *)malloc(length * sizeof(wchar_t));
	if (wp == NULL) {
		if (errno == ENOMEM)
			__archive_errx(1, "No memory");
		return (NULL);
	}
	count = 0;

	if ((want_type & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) != 0) {
		append_entry_w(&wp, NULL, ARCHIVE_ENTRY_ACL_TYPE_ACCESS,
		    ARCHIVE_ENTRY_ACL_USER_OBJ, flags, NULL,
		    acl->mode & 0700, -1);
		*wp++ = separator;
		append_entry_w(&wp, NULL, ARCHIVE_ENTRY_ACL_TYPE_ACCESS,
		    ARCHIVE_ENTRY_ACL_GROUP_OBJ, flags, NULL,
		    acl->mode & 0070, -1);
		*wp++ = separator;
		append_entry_w(&wp, NULL, ARCHIVE_ENTRY_ACL_TYPE_ACCESS,
		    ARCHIVE_ENTRY_ACL_OTHER, flags, NULL,
		    acl->mode & 0007, -1);
		count += 3;
	}

	for (ap = acl->acl_head; ap != NULL; ap = ap->next) {
		if ((ap->type & want_type) == 0)
			continue;
		/*
		 * Filemode-mapping ACL entries are stored exclusively in
		 * ap->mode so they should not be in the list
		 */
		if ((ap->type == ARCHIVE_ENTRY_ACL_TYPE_ACCESS)
		    && (ap->tag == ARCHIVE_ENTRY_ACL_USER_OBJ
		    || ap->tag == ARCHIVE_ENTRY_ACL_GROUP_OBJ
		    || ap->tag == ARCHIVE_ENTRY_ACL_OTHER))
			continue;
		if (ap->type == ARCHIVE_ENTRY_ACL_TYPE_DEFAULT &&
		    (flags & ARCHIVE_ENTRY_ACL_STYLE_MARK_DEFAULT) != 0)
			prefix = L"default:";
		else
			prefix = NULL;
		r = archive_mstring_get_wcs(a, &ap->name, &wname);
		if (r == 0) {
			if (count > 0)
				*wp++ = separator;
			if (flags & ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID)
				id = ap->id;
			else
				id = -1;
			append_entry_w(&wp, prefix, ap->type, ap->tag, flags,
			    wname, ap->permset, id);
			count++;
		} else if (r < 0 && errno == ENOMEM) {
			free(ws);
			return (NULL);
		}
	}

	/* Add terminating character */
	*wp++ = L'\0';

	len = wcslen(ws);

	if ((ssize_t)len > (length - 1))
		__archive_errx(1, "Buffer overrun");

	if (text_len != NULL)
		*text_len = len;

	return (ws);
}
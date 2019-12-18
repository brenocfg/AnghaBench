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
struct archive_string_conv {int dummy; } ;
struct archive_acl_entry {int type; scalar_t__ tag; int id; int permset; int /*<<< orphan*/  name; struct archive_acl_entry* next; } ;
struct archive_acl {int mode; struct archive_acl_entry* acl_head; } ;
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
 int /*<<< orphan*/  append_entry (char**,char const*,int,scalar_t__,int,char const*,int,int) ; 
 int archive_acl_text_len (struct archive_acl*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct archive_string_conv*) ; 
 int archive_acl_text_want_type (struct archive_acl*,int) ; 
 int archive_mstring_get_mbs_l (int /*<<< orphan*/ *,char const**,size_t*,struct archive_string_conv*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 size_t strlen (char*) ; 

char *
archive_acl_to_text_l(struct archive_acl *acl, ssize_t *text_len, int flags,
    struct archive_string_conv *sc)
{
	int count;
	ssize_t length;
	size_t len;
	const char *name;
	const char *prefix;
	char separator;
	struct archive_acl_entry *ap;
	int id, r, want_type;
	char *p, *s;

	want_type = archive_acl_text_want_type(acl, flags);

	/* Both NFSv4 and POSIX.1 types found */
	if (want_type == 0)
		return (NULL);

	if (want_type == ARCHIVE_ENTRY_ACL_TYPE_POSIX1E)
		flags |= ARCHIVE_ENTRY_ACL_STYLE_MARK_DEFAULT;

	length = archive_acl_text_len(acl, want_type, flags, 0, NULL, sc);

	if (length == 0)
		return (NULL);

	if (flags & ARCHIVE_ENTRY_ACL_STYLE_SEPARATOR_COMMA)
		separator = ',';
	else
		separator = '\n';

	/* Now, allocate the string and actually populate it. */
	p = s = (char *)malloc(length * sizeof(char));
	if (p == NULL) {
		if (errno == ENOMEM)
			__archive_errx(1, "No memory");
		return (NULL);
	}
	count = 0;

	if ((want_type & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) != 0) {
		append_entry(&p, NULL, ARCHIVE_ENTRY_ACL_TYPE_ACCESS,
		    ARCHIVE_ENTRY_ACL_USER_OBJ, flags, NULL,
		    acl->mode & 0700, -1);
		*p++ = separator;
		append_entry(&p, NULL, ARCHIVE_ENTRY_ACL_TYPE_ACCESS,
		    ARCHIVE_ENTRY_ACL_GROUP_OBJ, flags, NULL,
		    acl->mode & 0070, -1);
		*p++ = separator;
		append_entry(&p, NULL, ARCHIVE_ENTRY_ACL_TYPE_ACCESS,
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
			prefix = "default:";
		else
			prefix = NULL;
		r = archive_mstring_get_mbs_l(
		    &ap->name, &name, &len, sc);
		if (r != 0) {
			free(s);
			return (NULL);
		}
		if (count > 0)
			*p++ = separator;
		if (name == NULL ||
		    (flags & ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID)) {
			id = ap->id;
		} else {
			id = -1;
		}
		append_entry(&p, prefix, ap->type, ap->tag, flags, name,
		    ap->permset, id);
		count++;
	}

	/* Add terminating character */
	*p++ = '\0';

	len = strlen(s);

	if ((ssize_t)len > (length - 1))
		__archive_errx(1, "Buffer overrun");

	if (text_len != NULL)
		*text_len = len;

	return (s);
}
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
typedef  int /*<<< orphan*/ * acl_t ;

/* Variables and functions */
#define  ACL_BRAND_NFS4 129 
#define  ACL_BRAND_POSIX 128 
 int ACL_BRAND_UNKNOWN ; 
 void* EINVAL ; 
 int _acl_brand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _acl_brand_as (int /*<<< orphan*/ *,int) ; 
 int _nfs4_acl_entry_from_text (int /*<<< orphan*/ *,char*) ; 
 int _posix1e_acl_entry_from_text (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ _text_is_nfs4_entry (char*) ; 
 int /*<<< orphan*/  acl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * acl_init (int) ; 
 int acl_valid (int /*<<< orphan*/ *) ; 
 void* errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  string_skip_whitespace (char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 

acl_t
acl_from_text(const char *buf_p)
{
	acl_t		 acl;
	char		*mybuf_p, *line, *cur, *notcomment, *comment, *entry;
	int		 error;

	/* Local copy we can mess up. */
	mybuf_p = strdup(buf_p);
	if (mybuf_p == NULL)
		return(NULL);

	acl = acl_init(3); /* XXX: WTF, 3? */
	if (acl == NULL) {
		free(mybuf_p);
		return(NULL);
	}

	/* Outer loop: delimit at \n boundaries. */
	cur = mybuf_p;
	while ((line = strsep(&cur, "\n"))) {
		/* Now split the line on the first # to strip out comments. */
		comment = line;
		notcomment = strsep(&comment, "#");

		/* Inner loop: delimit at ',' boundaries. */
		while ((entry = strsep(&notcomment, ","))) {

			/* Skip empty lines. */
			if (strlen(string_skip_whitespace(entry)) == 0)
				continue;

			if (_acl_brand(acl) == ACL_BRAND_UNKNOWN) {
				if (_text_is_nfs4_entry(entry))
					_acl_brand_as(acl, ACL_BRAND_NFS4);
				else
					_acl_brand_as(acl, ACL_BRAND_POSIX);
			}

			switch (_acl_brand(acl)) {
			case ACL_BRAND_NFS4:
				error = _nfs4_acl_entry_from_text(acl, entry);
				break;

			case ACL_BRAND_POSIX:
				error = _posix1e_acl_entry_from_text(acl, entry);
				break;

			default:
				error = EINVAL;
				break;
			}

			if (error)
				goto error_label;
		}
	}

#if 0
	/* XXX Should we only return ACLs valid according to acl_valid? */
	/* Verify validity of the ACL we read in. */
	if (acl_valid(acl) == -1) {
		errno = EINVAL;
		goto error_label;
	}
#endif

	free(mybuf_p);
	return(acl);

error_label:
	acl_free(acl);
	free(mybuf_p);
	return(NULL);
}
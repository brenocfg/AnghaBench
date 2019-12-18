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
struct TYPE_3__ {char const* root; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */
 int BE_ERR_INVALIDNAME ; 
 int BE_ERR_PATHLEN ; 
 int BE_ERR_SUCCESS ; 
 size_t BE_MAXPATHLEN ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/ * strrchr (char const*,char) ; 
 char const* strstr (char const*,char const*) ; 

int
be_root_concat(libbe_handle_t *lbh, const char *name, char *result)
{
	size_t name_len, root_len;

	name_len = strlen(name);
	root_len = strlen(lbh->root);

	/* Act idempotently; return be name if it is already a full path */
	if (strrchr(name, '/') != NULL) {
		if (strstr(name, lbh->root) != name)
			return (BE_ERR_INVALIDNAME);

		if (name_len >= BE_MAXPATHLEN)
			return (BE_ERR_PATHLEN);

		strlcpy(result, name, BE_MAXPATHLEN);
		return (BE_ERR_SUCCESS);
	} else if (name_len + root_len + 1 < BE_MAXPATHLEN) {
		snprintf(result, BE_MAXPATHLEN, "%s/%s", lbh->root,
		    name);
		return (BE_ERR_SUCCESS);
	}

	return (BE_ERR_PATHLEN);
}
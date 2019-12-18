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
struct roff_node {scalar_t__ type; char* string; struct roff_node* next; struct roff_node* child; } ;

/* Variables and functions */
 scalar_t__ ROFFT_TEXT ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/  mandoc_asprintf (char**,char*,char*,int,char*) ; 
 char* mandoc_strndup (char*,size_t) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 size_t strlen (char*) ; 

void
deroff(char **dest, const struct roff_node *n)
{
	char	*cp;
	size_t	 sz;

	if (n->type != ROFFT_TEXT) {
		for (n = n->child; n != NULL; n = n->next)
			deroff(dest, n);
		return;
	}

	/* Skip leading whitespace. */

	for (cp = n->string; *cp != '\0'; cp++) {
		if (cp[0] == '\\' && cp[1] != '\0' &&
		    strchr(" %&0^|~", cp[1]) != NULL)
			cp++;
		else if ( ! isspace((unsigned char)*cp))
			break;
	}

	/* Skip trailing backslash. */

	sz = strlen(cp);
	if (sz > 0 && cp[sz - 1] == '\\')
		sz--;

	/* Skip trailing whitespace. */

	for (; sz; sz--)
		if ( ! isspace((unsigned char)cp[sz-1]))
			break;

	/* Skip empty strings. */

	if (sz == 0)
		return;

	if (*dest == NULL) {
		*dest = mandoc_strndup(cp, sz);
		return;
	}

	mandoc_asprintf(&cp, "%s %*s", *dest, (int)sz, cp);
	free(*dest);
	*dest = cp;
}
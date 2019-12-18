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
struct roff_node {scalar_t__ type; struct roff_node* next; struct roff_node* child; } ;

/* Variables and functions */
 scalar_t__ ROFFT_TEXT ; 
 int /*<<< orphan*/  deroff (char**,struct roff_node const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  id_unique ; 
 scalar_t__ isalnum (unsigned char) ; 
 int /*<<< orphan*/  mandoc_asprintf (char**,char*,char*,int) ; 
 char* ohash_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ohash_insert (int /*<<< orphan*/ *,unsigned int,char*) ; 
 unsigned int ohash_qlookup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

char *
html_make_id(const struct roff_node *n, int unique)
{
	const struct roff_node	*nch;
	char			*buf, *bufs, *cp;
	unsigned int		 slot;
	int			 suffix;

	for (nch = n->child; nch != NULL; nch = nch->next)
		if (nch->type != ROFFT_TEXT)
			return NULL;

	buf = NULL;
	deroff(&buf, n);
	if (buf == NULL)
		return NULL;

	/*
	 * In ID attributes, only use ASCII characters that are
	 * permitted in URL-fragment strings according to the
	 * explicit list at:
	 * https://url.spec.whatwg.org/#url-fragment-string
	 */

	for (cp = buf; *cp != '\0'; cp++)
		if (isalnum((unsigned char)*cp) == 0 &&
		    strchr("!$&'()*+,-./:;=?@_~", *cp) == NULL)
			*cp = '_';

	if (unique == 0)
		return buf;

	/* Avoid duplicate HTML id= attributes. */

	bufs = NULL;
	suffix = 1;
	slot = ohash_qlookup(&id_unique, buf);
	cp = ohash_find(&id_unique, slot);
	if (cp != NULL) {
		while (cp != NULL) {
			free(bufs);
			if (++suffix > 127) {
				free(buf);
				return NULL;
			}
			mandoc_asprintf(&bufs, "%s_%d", buf, suffix);
			slot = ohash_qlookup(&id_unique, bufs);
			cp = ohash_find(&id_unique, slot);
		}
		free(buf);
		buf = bufs;
	}
	ohash_insert(&id_unique, slot, buf);
	return buf;
}
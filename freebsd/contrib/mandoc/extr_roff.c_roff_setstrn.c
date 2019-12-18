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
struct TYPE_4__ {char* p; size_t sz; } ;
struct TYPE_3__ {size_t sz; int /*<<< orphan*/  p; } ;
struct roffkv {TYPE_2__ val; struct roffkv* next; TYPE_1__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 void* mandoc_malloc (size_t) ; 
 char* mandoc_realloc (char*,size_t) ; 
 int /*<<< orphan*/  mandoc_strndup (char const*,size_t) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static void
roff_setstrn(struct roffkv **r, const char *name, size_t namesz,
		const char *string, size_t stringsz, int append)
{
	struct roffkv	*n;
	char		*c;
	int		 i;
	size_t		 oldch, newch;

	/* Search for an existing string with the same name. */
	n = *r;

	while (n && (namesz != n->key.sz ||
			strncmp(n->key.p, name, namesz)))
		n = n->next;

	if (NULL == n) {
		/* Create a new string table entry. */
		n = mandoc_malloc(sizeof(struct roffkv));
		n->key.p = mandoc_strndup(name, namesz);
		n->key.sz = namesz;
		n->val.p = NULL;
		n->val.sz = 0;
		n->next = *r;
		*r = n;
	} else if (0 == append) {
		free(n->val.p);
		n->val.p = NULL;
		n->val.sz = 0;
	}

	if (NULL == string)
		return;

	/*
	 * One additional byte for the '\n' in multiline mode,
	 * and one for the terminating '\0'.
	 */
	newch = stringsz + (1 < append ? 2u : 1u);

	if (NULL == n->val.p) {
		n->val.p = mandoc_malloc(newch);
		*n->val.p = '\0';
		oldch = 0;
	} else {
		oldch = n->val.sz;
		n->val.p = mandoc_realloc(n->val.p, oldch + newch);
	}

	/* Skip existing content in the destination buffer. */
	c = n->val.p + (int)oldch;

	/* Append new content to the destination buffer. */
	i = 0;
	while (i < (int)stringsz) {
		/*
		 * Rudimentary roff copy mode:
		 * Handle escaped backslashes.
		 */
		if ('\\' == string[i] && '\\' == string[i + 1])
			i++;
		*c++ = string[i++];
	}

	/* Append terminating bytes. */
	if (1 < append)
		*c++ = '\n';

	*c = '\0';
	n->val.sz = (int)(c - n->val.p);
}
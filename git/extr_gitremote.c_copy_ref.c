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
struct ref {struct ref* peer_ref; void* remote_status; void* symref; int /*<<< orphan*/ * next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct ref*,struct ref const*,size_t) ; 
 size_t st_add3 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 struct ref* xmalloc (size_t) ; 
 void* xstrdup_or_null (void*) ; 

struct ref *copy_ref(const struct ref *ref)
{
	struct ref *cpy;
	size_t len;
	if (!ref)
		return NULL;
	len = st_add3(sizeof(struct ref), strlen(ref->name), 1);
	cpy = xmalloc(len);
	memcpy(cpy, ref, len);
	cpy->next = NULL;
	cpy->symref = xstrdup_or_null(ref->symref);
	cpy->remote_status = xstrdup_or_null(ref->remote_status);
	cpy->peer_ref = copy_ref(ref->peer_ref);
	return cpy;
}
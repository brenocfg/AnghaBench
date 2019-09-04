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
struct ref {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 
 int /*<<< orphan*/  st_add4 (int,size_t,size_t,int) ; 
 size_t strlen (char const*) ; 
 struct ref* xcalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ref *alloc_ref_with_prefix(const char *prefix, size_t prefixlen,
		const char *name)
{
	size_t len = strlen(name);
	struct ref *ref = xcalloc(1, st_add4(sizeof(*ref), prefixlen, len, 1));
	memcpy(ref->name, prefix, prefixlen);
	memcpy(ref->name + prefixlen, name, len);
	return ref;
}
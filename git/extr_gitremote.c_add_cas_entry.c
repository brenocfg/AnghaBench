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
struct push_cas_option {scalar_t__ nr; struct push_cas* entry; int /*<<< orphan*/  alloc; } ;
struct push_cas {int /*<<< orphan*/  refname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct push_cas*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct push_cas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xmemdupz (char const*,size_t) ; 

__attribute__((used)) static struct push_cas *add_cas_entry(struct push_cas_option *cas,
				      const char *refname,
				      size_t refnamelen)
{
	struct push_cas *entry;
	ALLOC_GROW(cas->entry, cas->nr + 1, cas->alloc);
	entry = &cas->entry[cas->nr++];
	memset(entry, 0, sizeof(*entry));
	entry->refname = xmemdupz(refname, refnamelen);
	return entry;
}
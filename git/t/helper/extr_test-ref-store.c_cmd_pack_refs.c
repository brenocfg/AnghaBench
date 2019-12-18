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
struct ref_store {int dummy; } ;

/* Variables and functions */
 unsigned int arg_flags (int /*<<< orphan*/ ,char*) ; 
 int refs_pack_refs (struct ref_store*,unsigned int) ; 

__attribute__((used)) static int cmd_pack_refs(struct ref_store *refs, const char **argv)
{
	unsigned int flags = arg_flags(*argv++, "flags");

	return refs_pack_refs(refs, flags);
}
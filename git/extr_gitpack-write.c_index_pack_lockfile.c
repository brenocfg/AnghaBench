#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int hexsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MAX_HEXSZ ; 
 int /*<<< orphan*/  get_object_directory () ; 
 int const read_in_full (int,char*,int const) ; 
 scalar_t__ skip_prefix (char*,char*,char const**) ; 
 TYPE_1__* the_hash_algo ; 
 char* xstrfmt (char*,int /*<<< orphan*/ ,char const*) ; 

char *index_pack_lockfile(int ip_out)
{
	char packname[GIT_MAX_HEXSZ + 6];
	const int len = the_hash_algo->hexsz + 6;

	/*
	 * The first thing we expect from index-pack's output
	 * is "pack\t%40s\n" or "keep\t%40s\n" (46 bytes) where
	 * %40s is the newly created pack SHA1 name.  In the "keep"
	 * case, we need it to remove the corresponding .keep file
	 * later on.  If we don't get that then tough luck with it.
	 */
	if (read_in_full(ip_out, packname, len) == len && packname[len-1] == '\n') {
		const char *name;
		packname[len-1] = 0;
		if (skip_prefix(packname, "keep\t", &name))
			return xstrfmt("%s/pack/pack-%s.keep",
				       get_object_directory(), name);
	}
	return NULL;
}
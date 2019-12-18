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
struct packed_git {int index_version; } ;
struct pack_idx_option {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 struct packed_git* add_packed_git (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close_pack_index (struct packed_git*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (struct packed_git*) ; 
 scalar_t__ open_pack_index (struct packed_git*) ; 
 int /*<<< orphan*/  read_v2_anomalous_offsets (struct packed_git*,struct pack_idx_option*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void read_idx_option(struct pack_idx_option *opts, const char *pack_name)
{
	struct packed_git *p = add_packed_git(pack_name, strlen(pack_name), 1);

	if (!p)
		die(_("Cannot open existing pack file '%s'"), pack_name);
	if (open_pack_index(p))
		die(_("Cannot open existing pack idx file for '%s'"), pack_name);

	/* Read the attributes from the existing idx file */
	opts->version = p->index_version;

	if (opts->version == 2)
		read_v2_anomalous_offsets(p, opts);

	/*
	 * Get rid of the idx file as we do not need it anymore.
	 * NEEDSWORK: extract this bit from free_pack_by_name() in
	 * sha1-file.c, perhaps?  It shouldn't matter very much as we
	 * know we haven't installed this pack (hence we never have
	 * read anything from it).
	 */
	close_pack_index(p);
	free(p);
}
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
struct packed_git {int /*<<< orphan*/  hash; int /*<<< orphan*/  pack_name; } ;

/* Variables and functions */
 struct packed_git* alloc_packed_git (size_t) ; 
 scalar_t__ check_packed_git_idx (char const*,struct packed_git*) ; 
 int /*<<< orphan*/  free (struct packed_git*) ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 char* sha1_pack_name (unsigned char*) ; 
 size_t st_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

struct packed_git *parse_pack_index(unsigned char *sha1, const char *idx_path)
{
	const char *path = sha1_pack_name(sha1);
	size_t alloc = st_add(strlen(path), 1);
	struct packed_git *p = alloc_packed_git(alloc);

	memcpy(p->pack_name, path, alloc); /* includes NUL */
	hashcpy(p->hash, sha1);
	if (check_packed_git_idx(idx_path, p)) {
		free(p);
		return NULL;
	}

	return p;
}
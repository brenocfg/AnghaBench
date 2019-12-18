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
struct stat {int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
struct packed_git {int pack_keep; int pack_promisor; int pack_local; int /*<<< orphan*/  hash; int /*<<< orphan*/  mtime; int /*<<< orphan*/  pack_size; scalar_t__ pack_name; } ;
struct TYPE_2__ {size_t hexsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  access (scalar_t__,int /*<<< orphan*/ ) ; 
 struct packed_git* alloc_packed_git (size_t) ; 
 int /*<<< orphan*/  free (struct packed_git*) ; 
 scalar_t__ get_sha1_hex (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashclr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 
 size_t st_add3 (size_t,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stat (scalar_t__,struct stat*) ; 
 int /*<<< orphan*/  strip_suffix_mem (char const*,size_t*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  xsnprintf (scalar_t__,size_t,char*) ; 

struct packed_git *add_packed_git(const char *path, size_t path_len, int local)
{
	struct stat st;
	size_t alloc;
	struct packed_git *p;

	/*
	 * Make sure a corresponding .pack file exists and that
	 * the index looks sane.
	 */
	if (!strip_suffix_mem(path, &path_len, ".idx"))
		return NULL;

	/*
	 * ".promisor" is long enough to hold any suffix we're adding (and
	 * the use xsnprintf double-checks that)
	 */
	alloc = st_add3(path_len, strlen(".promisor"), 1);
	p = alloc_packed_git(alloc);
	memcpy(p->pack_name, path, path_len);

	xsnprintf(p->pack_name + path_len, alloc - path_len, ".keep");
	if (!access(p->pack_name, F_OK))
		p->pack_keep = 1;

	xsnprintf(p->pack_name + path_len, alloc - path_len, ".promisor");
	if (!access(p->pack_name, F_OK))
		p->pack_promisor = 1;

	xsnprintf(p->pack_name + path_len, alloc - path_len, ".pack");
	if (stat(p->pack_name, &st) || !S_ISREG(st.st_mode)) {
		free(p);
		return NULL;
	}

	/* ok, it looks sane as far as we can check without
	 * actually mapping the pack file.
	 */
	p->pack_size = st.st_size;
	p->pack_local = local;
	p->mtime = st.st_mtime;
	if (path_len < the_hash_algo->hexsz ||
	    get_sha1_hex(path + path_len - the_hash_algo->hexsz, p->hash))
		hashclr(p->hash);
	return p;
}
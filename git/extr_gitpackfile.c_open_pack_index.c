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
struct packed_git {int /*<<< orphan*/  pack_name; scalar_t__ index_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int check_packed_git_idx (char*,struct packed_git*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strip_suffix (int /*<<< orphan*/ ,char*,size_t*) ; 
 char* xstrfmt (char*,int,int /*<<< orphan*/ ) ; 

int open_pack_index(struct packed_git *p)
{
	char *idx_name;
	size_t len;
	int ret;

	if (p->index_data)
		return 0;

	if (!strip_suffix(p->pack_name, ".pack", &len))
		BUG("pack_name does not end in .pack");
	idx_name = xstrfmt("%.*s.idx", (int)len, p->pack_name);
	ret = check_packed_git_idx(idx_name, p);
	free(idx_name);
	return ret;
}
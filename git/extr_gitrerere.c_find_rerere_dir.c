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
struct rerere_dir {scalar_t__ status_alloc; scalar_t__ status_nr; int /*<<< orphan*/ * status; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct rerere_dir**,int,int /*<<< orphan*/ ) ; 
 int GIT_MAX_RAWSZ ; 
 int /*<<< orphan*/  MOVE_ARRAY (struct rerere_dir**,struct rerere_dir**,int) ; 
 scalar_t__ get_sha1_hex (char const*,unsigned char*) ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,unsigned char*) ; 
 struct rerere_dir** rerere_dir ; 
 int /*<<< orphan*/  rerere_dir_alloc ; 
 int /*<<< orphan*/  rerere_dir_hash ; 
 int rerere_dir_nr ; 
 int /*<<< orphan*/  scan_rerere_dir (struct rerere_dir*) ; 
 int sha1_pos (unsigned char*,struct rerere_dir**,int,int /*<<< orphan*/ ) ; 
 struct rerere_dir* xmalloc (int) ; 

__attribute__((used)) static struct rerere_dir *find_rerere_dir(const char *hex)
{
	unsigned char hash[GIT_MAX_RAWSZ];
	struct rerere_dir *rr_dir;
	int pos;

	if (get_sha1_hex(hex, hash))
		return NULL; /* BUG */
	pos = sha1_pos(hash, rerere_dir, rerere_dir_nr, rerere_dir_hash);
	if (pos < 0) {
		rr_dir = xmalloc(sizeof(*rr_dir));
		hashcpy(rr_dir->hash, hash);
		rr_dir->status = NULL;
		rr_dir->status_nr = 0;
		rr_dir->status_alloc = 0;
		pos = -1 - pos;

		/* Make sure the array is big enough ... */
		ALLOC_GROW(rerere_dir, rerere_dir_nr + 1, rerere_dir_alloc);
		/* ... and add it in. */
		rerere_dir_nr++;
		MOVE_ARRAY(rerere_dir + pos + 1, rerere_dir + pos,
			   rerere_dir_nr - pos - 1);
		rerere_dir[pos] = rr_dir;
		scan_rerere_dir(rr_dir);
	}
	return rerere_dir[pos];
}
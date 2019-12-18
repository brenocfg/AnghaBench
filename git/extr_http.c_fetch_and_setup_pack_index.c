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
struct packed_git {struct packed_git* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_pack_index (struct packed_git*) ; 
 char* fetch_pack_index (unsigned char*,char const*) ; 
 int finalize_object_file (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ has_pack_index (unsigned char*) ; 
 struct packed_git* parse_pack_index (unsigned char*,char*) ; 
 char* sha1_pack_index_name (unsigned char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int verify_pack_index (struct packed_git*) ; 

__attribute__((used)) static int fetch_and_setup_pack_index(struct packed_git **packs_head,
	unsigned char *sha1, const char *base_url)
{
	struct packed_git *new_pack;
	char *tmp_idx = NULL;
	int ret;

	if (has_pack_index(sha1)) {
		new_pack = parse_pack_index(sha1, sha1_pack_index_name(sha1));
		if (!new_pack)
			return -1; /* parse_pack_index() already issued error message */
		goto add_pack;
	}

	tmp_idx = fetch_pack_index(sha1, base_url);
	if (!tmp_idx)
		return -1;

	new_pack = parse_pack_index(sha1, tmp_idx);
	if (!new_pack) {
		unlink(tmp_idx);
		free(tmp_idx);

		return -1; /* parse_pack_index() already issued error message */
	}

	ret = verify_pack_index(new_pack);
	if (!ret) {
		close_pack_index(new_pack);
		ret = finalize_object_file(tmp_idx, sha1_pack_index_name(sha1));
	}
	free(tmp_idx);
	if (ret)
		return -1;

add_pack:
	new_pack->next = *packs_head;
	*packs_head = new_pack;
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct string_list {int dummy; } ;
struct strbuf {unsigned int const len; char* buf; } ;
struct rerere_id {int variant; } ;
struct repository {int dummy; } ;
struct TYPE_4__ {struct rerere_id* util; } ;
struct TYPE_3__ {unsigned int hexsz; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int GIT_MAX_RAWSZ ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_sha1_hex (char*,unsigned char*) ; 
 int /*<<< orphan*/  git_path_merge_rr (struct repository*) ; 
 struct rerere_id* new_rerere_id_hex (char*) ; 
 int /*<<< orphan*/  strbuf_getwholeline (struct strbuf*,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 TYPE_2__* string_list_insert (struct string_list*,char*) ; 
 int strtol (char*,char**,int) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static void read_rr(struct repository *r, struct string_list *rr)
{
	struct strbuf buf = STRBUF_INIT;
	FILE *in = fopen_or_warn(git_path_merge_rr(r), "r");

	if (!in)
		return;
	while (!strbuf_getwholeline(&buf, in, '\0')) {
		char *path;
		unsigned char hash[GIT_MAX_RAWSZ];
		struct rerere_id *id;
		int variant;
		const unsigned hexsz = the_hash_algo->hexsz;

		/* There has to be the hash, tab, path and then NUL */
		if (buf.len < hexsz + 2 || get_sha1_hex(buf.buf, hash))
			die(_("corrupt MERGE_RR"));

		if (buf.buf[hexsz] != '.') {
			variant = 0;
			path = buf.buf + hexsz;
		} else {
			errno = 0;
			variant = strtol(buf.buf + hexsz + 1, &path, 10);
			if (errno)
				die(_("corrupt MERGE_RR"));
		}
		if (*(path++) != '\t')
			die(_("corrupt MERGE_RR"));
		buf.buf[hexsz] = '\0';
		id = new_rerere_id_hex(buf.buf);
		id->variant = variant;
		string_list_insert(rr, path)->util = id;
	}
	strbuf_release(&buf);
	fclose(in);
}
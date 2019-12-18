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
struct packed_git {int /*<<< orphan*/  hash; struct packed_git* next; } ;
struct TYPE_2__ {char* buf; } ;
struct http_pack_request {TYPE_1__ tmpfile; struct packed_git** lst; int /*<<< orphan*/ * packfile; struct packed_git* target; } ;
struct child_process {int git_cmd; int no_stdin; int no_stdout; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_pack_index (struct packed_git*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ finalize_object_file (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  install_packed_git (int /*<<< orphan*/ ,struct packed_git*) ; 
 scalar_t__ run_command (struct child_process*) ; 
 char* sha1_pack_index_name (int /*<<< orphan*/ ) ; 
 char* sha1_pack_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_suffix (char*,char*,size_t*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  unlink (char*) ; 
 char* xstrfmt (char*,int,char*) ; 

int finish_http_pack_request(struct http_pack_request *preq)
{
	struct packed_git **lst;
	struct packed_git *p = preq->target;
	char *tmp_idx;
	size_t len;
	struct child_process ip = CHILD_PROCESS_INIT;

	close_pack_index(p);

	fclose(preq->packfile);
	preq->packfile = NULL;

	lst = preq->lst;
	while (*lst != p)
		lst = &((*lst)->next);
	*lst = (*lst)->next;

	if (!strip_suffix(preq->tmpfile.buf, ".pack.temp", &len))
		BUG("pack tmpfile does not end in .pack.temp?");
	tmp_idx = xstrfmt("%.*s.idx.temp", (int)len, preq->tmpfile.buf);

	argv_array_push(&ip.args, "index-pack");
	argv_array_pushl(&ip.args, "-o", tmp_idx, NULL);
	argv_array_push(&ip.args, preq->tmpfile.buf);
	ip.git_cmd = 1;
	ip.no_stdin = 1;
	ip.no_stdout = 1;

	if (run_command(&ip)) {
		unlink(preq->tmpfile.buf);
		unlink(tmp_idx);
		free(tmp_idx);
		return -1;
	}

	unlink(sha1_pack_index_name(p->hash));

	if (finalize_object_file(preq->tmpfile.buf, sha1_pack_name(p->hash))
	 || finalize_object_file(tmp_idx, sha1_pack_index_name(p->hash))) {
		free(tmp_idx);
		return -1;
	}

	install_packed_git(the_repository, p);
	free(tmp_idx);
	return 0;
}
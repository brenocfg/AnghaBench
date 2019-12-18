#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  key; int /*<<< orphan*/  seq; int /*<<< orphan*/  mode; int /*<<< orphan*/  pgid; int /*<<< orphan*/  puid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct TYPE_6__ {TYPE_1__ ipcperm; } ;
struct TYPE_7__ {TYPE_2__ tt; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ tokenstr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AU_OFLAG_XML ; 
 int /*<<< orphan*/  close_attr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_attr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_4_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_delim (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_tok_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  print_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
print_ipcperm_tok(FILE *fp, tokenstr_t *tok, char *del, int oflags)
{

	print_tok_type(fp, tok->id, "IPC perm", oflags);
	if (oflags & AU_OFLAG_XML) {
		open_attr(fp, "uid");
		print_user(fp, tok->tt.ipcperm.uid, oflags);
		close_attr(fp);
		open_attr(fp, "gid");
		print_group(fp, tok->tt.ipcperm.gid, oflags);
		close_attr(fp);
		open_attr(fp, "creator-uid");
		print_user(fp, tok->tt.ipcperm.puid, oflags);
		close_attr(fp);
		open_attr(fp, "creator-gid");
		print_group(fp, tok->tt.ipcperm.pgid, oflags);
		close_attr(fp);
		open_attr(fp, "mode");
		print_4_bytes(fp, tok->tt.ipcperm.mode, "%o");
		close_attr(fp);
		open_attr(fp, "seq");
		print_4_bytes(fp, tok->tt.ipcperm.seq, "%u");
		close_attr(fp);
		open_attr(fp, "key");
		print_4_bytes(fp, tok->tt.ipcperm.key, "%u");
		close_attr(fp);
		close_tag(fp, tok->id);
	} else {
		print_delim(fp, del);
		print_user(fp, tok->tt.ipcperm.uid, oflags);
		print_delim(fp, del);
		print_group(fp, tok->tt.ipcperm.gid, oflags);
		print_delim(fp, del);
		print_user(fp, tok->tt.ipcperm.puid, oflags);
		print_delim(fp, del);
		print_group(fp, tok->tt.ipcperm.pgid, oflags);
		print_delim(fp, del);
		print_4_bytes(fp, tok->tt.ipcperm.mode, "%o");
		print_delim(fp, del);
		print_4_bytes(fp, tok->tt.ipcperm.seq, "%u");
		print_delim(fp, del);
		print_4_bytes(fp, tok->tt.ipcperm.key, "%u");
	}
}
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
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  nid; int /*<<< orphan*/  fsid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {TYPE_1__ attr64; } ;
struct TYPE_7__ {TYPE_2__ tt; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ tokenstr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AU_OFLAG_XML ; 
 int /*<<< orphan*/  close_attr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_attr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_4_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_8_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_delim (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_tok_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  print_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
print_attr64_tok(FILE *fp, tokenstr_t *tok, char *del, int oflags)
{

	print_tok_type(fp, tok->id, "attribute", oflags);
	if (oflags & AU_OFLAG_XML) {
		open_attr(fp, "mode");
		print_4_bytes(fp, tok->tt.attr64.mode, "%o");
		close_attr(fp);
		open_attr(fp, "uid");
		print_user(fp, tok->tt.attr64.uid, oflags);
		close_attr(fp);
		open_attr(fp, "gid");
		print_group(fp, tok->tt.attr64.gid, oflags);
		close_attr(fp);
		open_attr(fp, "fsid");
		print_4_bytes(fp, tok->tt.attr64.fsid, "%u");
		close_attr(fp);
		open_attr(fp, "nodeid");
		print_8_bytes(fp, tok->tt.attr64.nid, "%lld");
		close_attr(fp);
		open_attr(fp, "device");
		print_8_bytes(fp, tok->tt.attr64.dev, "%llu");
		close_attr(fp);
		close_tag(fp, tok->id);
	} else {
		print_delim(fp, del);
		print_4_bytes(fp, tok->tt.attr64.mode, "%o");
		print_delim(fp, del);
		print_user(fp, tok->tt.attr64.uid, oflags);
		print_delim(fp, del);
		print_group(fp, tok->tt.attr64.gid, oflags);
		print_delim(fp, del);
		print_4_bytes(fp, tok->tt.attr64.fsid, "%u");
		print_delim(fp, del);
		print_8_bytes(fp, tok->tt.attr64.nid, "%lld");
		print_delim(fp, del);
		print_8_bytes(fp, tok->tt.attr64.dev, "%llu");
	}
}
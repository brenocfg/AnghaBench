#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; int /*<<< orphan*/  port; } ;
struct TYPE_7__ {TYPE_1__ tid; int /*<<< orphan*/  sid; int /*<<< orphan*/  pid; int /*<<< orphan*/  rgid; int /*<<< orphan*/  ruid; int /*<<< orphan*/  egid; int /*<<< orphan*/  euid; int /*<<< orphan*/  auid; } ;
struct TYPE_8__ {TYPE_2__ proc64_ex; } ;
struct TYPE_9__ {TYPE_3__ tt; int /*<<< orphan*/  id; } ;
typedef  TYPE_4__ tokenstr_t ;
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
 int /*<<< orphan*/  print_ip_ex_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_tok_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  print_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
print_process64ex_tok(FILE *fp, tokenstr_t *tok, char *del, int oflags)
{
	print_tok_type(fp, tok->id, "process_ex", oflags);
	if (oflags & AU_OFLAG_XML) {
		open_attr(fp, "audit-uid");
		print_user(fp, tok->tt.proc64_ex.auid, oflags);
		close_attr(fp);
		open_attr(fp, "uid");
		print_user(fp, tok->tt.proc64_ex.euid, oflags);
		close_attr(fp);
		open_attr(fp, "gid");
		print_group(fp, tok->tt.proc64_ex.egid, oflags);
		close_attr(fp);
		open_attr(fp, "ruid");
		print_user(fp, tok->tt.proc64_ex.ruid, oflags);
		close_attr(fp);
		open_attr(fp, "rgid");
		print_group(fp, tok->tt.proc64_ex.rgid, oflags);
		close_attr(fp);
		open_attr(fp, "pid");
		print_4_bytes(fp, tok->tt.proc64_ex.pid, "%u");
		close_attr(fp);
		open_attr(fp, "sid");
		print_4_bytes(fp, tok->tt.proc64_ex.sid, "%u");
		close_attr(fp);
		open_attr(fp, "tid");
		print_8_bytes(fp, tok->tt.proc64_ex.tid.port, "%llu");
		print_ip_ex_address(fp, tok->tt.proc64_ex.tid.type,
		    tok->tt.proc64_ex.tid.addr);
		close_attr(fp);
		close_tag(fp, tok->id);
	} else {
		print_delim(fp, del);
		print_user(fp, tok->tt.proc64_ex.auid, oflags);
		print_delim(fp, del);
		print_user(fp, tok->tt.proc64_ex.euid, oflags);
		print_delim(fp, del);
		print_group(fp, tok->tt.proc64_ex.egid, oflags);
		print_delim(fp, del);
		print_user(fp, tok->tt.proc64_ex.ruid, oflags);
		print_delim(fp, del);
		print_group(fp, tok->tt.proc64_ex.rgid, oflags);
		print_delim(fp, del);
		print_4_bytes(fp, tok->tt.proc64_ex.pid, "%u");
		print_delim(fp, del);
		print_4_bytes(fp, tok->tt.proc64_ex.sid, "%u");
		print_delim(fp, del);
		print_8_bytes(fp, tok->tt.proc64_ex.tid.port, "%llu");
		print_delim(fp, del);
		print_ip_ex_address(fp, tok->tt.proc64_ex.tid.type,
		    tok->tt.proc64_ex.tid.addr);
	}
}
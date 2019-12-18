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
struct TYPE_5__ {int /*<<< orphan*/  ms; int /*<<< orphan*/  s; int /*<<< orphan*/  addr; int /*<<< orphan*/  ad_type; int /*<<< orphan*/  e_mod; int /*<<< orphan*/  e_type; int /*<<< orphan*/  version; int /*<<< orphan*/  size; } ;
struct TYPE_6__ {TYPE_1__ hdr32_ex; } ;
struct TYPE_7__ {TYPE_2__ tt; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ tokenstr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AU_OFLAG_RAW ; 
 int /*<<< orphan*/  close_attr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_attr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_1_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_4_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_delim (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_evmod (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_ip_ex_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_msec32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_sec32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_tok_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
print_header32_ex_tok(FILE *fp, tokenstr_t *tok, char *del, int oflags)
{

	print_tok_type(fp, tok->id, "header_ex", oflags);
	if (oflags & AU_OFLAG_RAW) {
		open_attr(fp, "version");
		print_1_byte(fp, tok->tt.hdr32_ex.version, "%u");
		close_attr(fp);
		open_attr(fp, "event");
		print_event(fp, tok->tt.hdr32_ex.e_type, oflags);
		close_attr(fp);
		open_attr(fp, "modifier");
		print_evmod(fp, tok->tt.hdr32_ex.e_mod, oflags);
		close_attr(fp);
		open_attr(fp, "host");
		print_ip_ex_address(fp, tok->tt.hdr32_ex.ad_type,
		    tok->tt.hdr32_ex.addr);
		close_attr(fp);
		open_attr(fp, "time");
		print_sec32(fp, tok->tt.hdr32_ex.s, oflags);
		close_attr(fp);
		open_attr(fp, "msec");
		print_msec32(fp, tok->tt.hdr32_ex.ms, oflags);
		close_attr(fp);
		close_tag(fp, tok->id);
	} else {
		print_delim(fp, del);
		print_4_bytes(fp, tok->tt.hdr32_ex.size, "%u");
		print_delim(fp, del);
		print_1_byte(fp, tok->tt.hdr32_ex.version, "%u");
		print_delim(fp, del);
		print_event(fp, tok->tt.hdr32_ex.e_type, oflags);
		print_delim(fp, del);
		print_evmod(fp, tok->tt.hdr32_ex.e_mod, oflags);
		print_delim(fp, del);
		print_ip_ex_address(fp, tok->tt.hdr32_ex.ad_type,
		    tok->tt.hdr32_ex.addr);
		print_delim(fp, del);
		print_sec32(fp, tok->tt.hdr32_ex.s, oflags);
		print_delim(fp, del);
		print_msec32(fp, tok->tt.hdr32_ex.ms, oflags);
	}
}
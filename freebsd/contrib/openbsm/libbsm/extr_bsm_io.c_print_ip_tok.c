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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int /*<<< orphan*/  dest; int /*<<< orphan*/  src; int /*<<< orphan*/  chksm; int /*<<< orphan*/  prot; int /*<<< orphan*/  ttl; int /*<<< orphan*/  offset; int /*<<< orphan*/  id; int /*<<< orphan*/  len; int /*<<< orphan*/  tos; int /*<<< orphan*/  version; } ;
struct TYPE_6__ {TYPE_1__ ip; } ;
struct TYPE_7__ {TYPE_2__ tt; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ tokenstr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AU_OFLAG_XML ; 
 int /*<<< orphan*/  close_attr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_attr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_2_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_delim (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_ip_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_tok_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
print_ip_tok(FILE *fp, tokenstr_t *tok, char *del, int oflags)
{

	print_tok_type(fp, tok->id, "ip", oflags);
	if (oflags & AU_OFLAG_XML) {
		open_attr(fp, "version");
		print_mem(fp, (u_char *)(&tok->tt.ip.version),
		    sizeof(u_char));
		close_attr(fp);
		open_attr(fp, "service_type");
		print_mem(fp, (u_char *)(&tok->tt.ip.tos), sizeof(u_char));
		close_attr(fp);
		open_attr(fp, "len");
		print_2_bytes(fp, ntohs(tok->tt.ip.len), "%u");
		close_attr(fp);
		open_attr(fp, "id");
		print_2_bytes(fp, ntohs(tok->tt.ip.id), "%u");
		close_attr(fp);
		open_attr(fp, "offset");
		print_2_bytes(fp, ntohs(tok->tt.ip.offset), "%u");
		close_attr(fp);
		open_attr(fp, "time_to_live");
		print_mem(fp, (u_char *)(&tok->tt.ip.ttl), sizeof(u_char));
		close_attr(fp);
		open_attr(fp, "protocol");
		print_mem(fp, (u_char *)(&tok->tt.ip.prot), sizeof(u_char));
		close_attr(fp);
		open_attr(fp, "cksum");
		print_2_bytes(fp, ntohs(tok->tt.ip.chksm), "%u");
		close_attr(fp);
		open_attr(fp, "src_addr");
		print_ip_address(fp, tok->tt.ip.src);
		close_attr(fp);
		open_attr(fp, "dest_addr");
		print_ip_address(fp, tok->tt.ip.dest);
		close_attr(fp);
		close_tag(fp, tok->id);
	} else {
		print_delim(fp, del);
		print_mem(fp, (u_char *)(&tok->tt.ip.version),
		    sizeof(u_char));
		print_delim(fp, del);
		print_mem(fp, (u_char *)(&tok->tt.ip.tos), sizeof(u_char));
		print_delim(fp, del);
		print_2_bytes(fp, ntohs(tok->tt.ip.len), "%u");
		print_delim(fp, del);
		print_2_bytes(fp, ntohs(tok->tt.ip.id), "%u");
		print_delim(fp, del);
		print_2_bytes(fp, ntohs(tok->tt.ip.offset), "%u");
		print_delim(fp, del);
		print_mem(fp, (u_char *)(&tok->tt.ip.ttl), sizeof(u_char));
		print_delim(fp, del);
		print_mem(fp, (u_char *)(&tok->tt.ip.prot), sizeof(u_char));
		print_delim(fp, del);
		print_2_bytes(fp, ntohs(tok->tt.ip.chksm), "%u");
		print_delim(fp, del);
		print_ip_address(fp, tok->tt.ip.src);
		print_delim(fp, del);
		print_ip_address(fp, tok->tt.ip.dest);
	}
}
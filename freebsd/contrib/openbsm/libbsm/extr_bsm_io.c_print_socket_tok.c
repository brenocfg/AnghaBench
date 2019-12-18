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
struct TYPE_5__ {int /*<<< orphan*/  r_addr; int /*<<< orphan*/  r_port; int /*<<< orphan*/  l_addr; int /*<<< orphan*/  l_port; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_1__ socket; } ;
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
 int /*<<< orphan*/  print_tok_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
print_socket_tok(FILE *fp, tokenstr_t *tok, char *del, int oflags)
{

	print_tok_type(fp, tok->id, "socket", oflags);
	if (oflags & AU_OFLAG_XML) {
		open_attr(fp, "sock_type");
		print_2_bytes(fp, tok->tt.socket.type, "%u");
		close_attr(fp);
		open_attr(fp, "lport");
		print_2_bytes(fp, ntohs(tok->tt.socket.l_port), "%u");
		close_attr(fp);
		open_attr(fp, "laddr");
		print_ip_address(fp, tok->tt.socket.l_addr);
		close_attr(fp);
		open_attr(fp, "fport");
		print_2_bytes(fp, ntohs(tok->tt.socket.r_port), "%u");
		close_attr(fp);
		open_attr(fp, "faddr");
		print_ip_address(fp, tok->tt.socket.r_addr);
		close_attr(fp);
		close_tag(fp, tok->id);
	} else {
		print_delim(fp, del);
		print_2_bytes(fp, tok->tt.socket.type, "%u");
		print_delim(fp, del);
		print_2_bytes(fp, ntohs(tok->tt.socket.l_port), "%u");
		print_delim(fp, del);
		print_ip_address(fp, tok->tt.socket.l_addr);
		print_delim(fp, del);
		print_2_bytes(fp, ntohs(tok->tt.socket.r_port), "%u");
		print_delim(fp, del);
		print_ip_address(fp, tok->tt.socket.r_addr);
	}
}
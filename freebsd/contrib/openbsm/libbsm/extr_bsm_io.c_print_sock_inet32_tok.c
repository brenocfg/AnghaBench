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
struct TYPE_5__ {int /*<<< orphan*/ * addr; int /*<<< orphan*/  port; int /*<<< orphan*/  family; } ;
struct TYPE_6__ {TYPE_1__ sockinet_ex32; } ;
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
print_sock_inet32_tok(FILE *fp, tokenstr_t *tok, char *del, int oflags)
{

	print_tok_type(fp, tok->id, "socket-inet", oflags);
	if (oflags & AU_OFLAG_XML) {
		open_attr(fp, "type");
		print_2_bytes(fp, tok->tt.sockinet_ex32.family, "%u");
		close_attr(fp);
		open_attr(fp, "port");
		print_2_bytes(fp, ntohs(tok->tt.sockinet_ex32.port), "%u");
		close_attr(fp);
		open_attr(fp, "addr");
		print_ip_address(fp, tok->tt.sockinet_ex32.addr[0]);
		close_attr(fp);
		close_tag(fp, tok->id);
	} else {
		print_delim(fp, del);
		print_2_bytes(fp, tok->tt.sockinet_ex32.family, "%u");
		print_delim(fp, del);
		print_2_bytes(fp, ntohs(tok->tt.sockinet_ex32.port), "%u");
		print_delim(fp, del);
		print_ip_address(fp, tok->tt.sockinet_ex32.addr[0]);
	}
}
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
struct interface_info {int dummy; } ;
struct client_lease {int is_bootp; int /*<<< orphan*/  options; void* expiry; void* rebind; void* renewal; void* server_name; int /*<<< orphan*/  nextserver; void* filename; int /*<<< orphan*/  medium; int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  BOOTP 138 
#define  EXPIRE 137 
#define  FILENAME 136 
#define  FIXED_ADDR 135 
#define  INTERFACE 134 
#define  MEDIUM 133 
#define  NEXT_SERVER 132 
#define  OPTION 131 
#define  REBIND 130 
#define  RENEW 129 
 int SEMI ; 
#define  SERVER_NAME 128 
 int STRING ; 
 struct interface_info* interface_or_dummy (char*) ; 
 int next_token (char**,int /*<<< orphan*/ *) ; 
 void* parse_date (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_ip_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_option_decl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* parse_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_string_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_warn (char*) ; 
 int /*<<< orphan*/  skip_to_semi (int /*<<< orphan*/ *) ; 

void
parse_client_lease_declaration(FILE *cfile, struct client_lease *lease,
    struct interface_info **ipp)
{
	int			 token;
	char			*val;
	struct interface_info	*ip;

	switch (next_token(&val, cfile)) {
	case BOOTP:
		lease->is_bootp = 1;
		break;
	case INTERFACE:
		token = next_token(&val, cfile);
		if (token != STRING) {
			parse_warn("expecting interface name (in quotes).");
			skip_to_semi(cfile);
			break;
		}
		ip = interface_or_dummy(val);
		*ipp = ip;
		break;
	case FIXED_ADDR:
		if (!parse_ip_addr(cfile, &lease->address))
			return;
		break;
	case MEDIUM:
		parse_string_list(cfile, &lease->medium, 0);
		return;
	case FILENAME:
		lease->filename = parse_string(cfile);
		return;
	case NEXT_SERVER:
		if (!parse_ip_addr(cfile, &lease->nextserver))
			return;
		break;
	case SERVER_NAME:
		lease->server_name = parse_string(cfile);
		return;
	case RENEW:
		lease->renewal = parse_date(cfile);
		return;
	case REBIND:
		lease->rebind = parse_date(cfile);
		return;
	case EXPIRE:
		lease->expiry = parse_date(cfile);
		return;
	case OPTION:
		parse_option_decl(cfile, lease->options);
		return;
	default:
		parse_warn("expecting lease declaration.");
		skip_to_semi(cfile);
		break;
	}
	token = next_token(&val, cfile);
	if (token != SEMI) {
		parse_warn("expecting semicolon.");
		skip_to_semi(cfile);
	}
}
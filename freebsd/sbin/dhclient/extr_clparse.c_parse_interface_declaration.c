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
struct interface_info {TYPE_1__* client; } ;
struct client_config {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  config; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int LBRACE ; 
 int RBRACE ; 
 int STRING ; 
 struct interface_info* interface_or_dummy (char*) ; 
 int /*<<< orphan*/  make_client_config (struct interface_info*,struct client_config*) ; 
 int /*<<< orphan*/  make_client_state (struct interface_info*) ; 
 int next_token (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_client_statement (int /*<<< orphan*/ *,struct interface_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_warn (char*) ; 
 int peek_token (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_to_semi (int /*<<< orphan*/ *) ; 

void
parse_interface_declaration(FILE *cfile, struct client_config *outer_config)
{
	int			 token;
	char			*val;
	struct interface_info	*ip;

	token = next_token(&val, cfile);
	if (token != STRING) {
		parse_warn("expecting interface name (in quotes).");
		skip_to_semi(cfile);
		return;
	}

	ip = interface_or_dummy(val);

	if (!ip->client)
		make_client_state(ip);

	if (!ip->client->config)
		make_client_config(ip, outer_config);

	token = next_token(&val, cfile);
	if (token != LBRACE) {
		parse_warn("expecting left brace.");
		skip_to_semi(cfile);
		return;
	}

	do {
		token = peek_token(&val, cfile);
		if (token == EOF) {
			parse_warn("unterminated interface declaration.");
			return;
		}
		if (token == RBRACE)
			break;
		parse_client_statement(cfile, ip, ip->client->config);
	} while (1);
	token = next_token(&val, cfile);
}
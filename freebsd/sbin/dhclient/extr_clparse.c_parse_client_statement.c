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
struct option {size_t code; } ;
struct interface_info {int /*<<< orphan*/  hw_address; } ;
struct client_config {int /*<<< orphan*/  script_name; int /*<<< orphan*/  initial_interval; int /*<<< orphan*/  backoff_cutoff; int /*<<< orphan*/  reboot_timeout; int /*<<< orphan*/  select_interval; int /*<<< orphan*/  retry_interval; int /*<<< orphan*/  timeout; int /*<<< orphan*/  required_options; int /*<<< orphan*/  requested_options; int /*<<< orphan*/  requested_option_count; int /*<<< orphan*/  media; int /*<<< orphan*/ * default_actions; int /*<<< orphan*/ * defaults; int /*<<< orphan*/ * send_options; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_APPEND ; 
 int /*<<< orphan*/  ACTION_DEFAULT ; 
 int /*<<< orphan*/  ACTION_PREPEND ; 
 int /*<<< orphan*/  ACTION_SUPERSEDE ; 
#define  ALIAS 147 
#define  APPEND 146 
#define  BACKOFF_CUTOFF 145 
#define  DEFAULT 144 
#define  HARDWARE 143 
#define  INITIAL_INTERVAL 142 
#define  INTERFACE 141 
#define  LEASE 140 
#define  MEDIA 139 
#define  PREPEND 138 
#define  REBOOT 137 
#define  REJECT 136 
#define  REQUEST 135 
#define  REQUIRE 134 
#define  RETRY 133 
#define  SCRIPT 132 
#define  SELECT_TIMEOUT 131 
 int SEMI ; 
#define  SEND 130 
#define  SUPERSEDE 129 
#define  TIMEOUT 128 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int next_token (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_client_lease_statement (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  parse_hardware_param (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_interface_declaration (int /*<<< orphan*/ *,struct client_config*) ; 
 int /*<<< orphan*/  parse_lease_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct option* parse_option_decl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_option_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_reject_statement (int /*<<< orphan*/ *,struct client_config*) ; 
 int /*<<< orphan*/  parse_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_string_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  parse_warn (char*,...) ; 
 int /*<<< orphan*/  skip_to_semi (int /*<<< orphan*/ *) ; 

void
parse_client_statement(FILE *cfile, struct interface_info *ip,
    struct client_config *config)
{
	int		 token;
	char		*val;
	struct option	*option;

	switch (next_token(&val, cfile)) {
	case SEND:
		parse_option_decl(cfile, &config->send_options[0]);
		return;
	case DEFAULT:
		option = parse_option_decl(cfile, &config->defaults[0]);
		if (option)
			config->default_actions[option->code] = ACTION_DEFAULT;
		return;
	case SUPERSEDE:
		option = parse_option_decl(cfile, &config->defaults[0]);
		if (option)
			config->default_actions[option->code] =
			    ACTION_SUPERSEDE;
		return;
	case APPEND:
		option = parse_option_decl(cfile, &config->defaults[0]);
		if (option)
			config->default_actions[option->code] = ACTION_APPEND;
		return;
	case PREPEND:
		option = parse_option_decl(cfile, &config->defaults[0]);
		if (option)
			config->default_actions[option->code] = ACTION_PREPEND;
		return;
	case MEDIA:
		parse_string_list(cfile, &config->media, 1);
		return;
	case HARDWARE:
		if (ip)
			parse_hardware_param(cfile, &ip->hw_address);
		else {
			parse_warn("hardware address parameter %s",
				    "not allowed here.");
			skip_to_semi(cfile);
		}
		return;
	case REQUEST:
		config->requested_option_count =
			parse_option_list(cfile, config->requested_options);
		return;
	case REQUIRE:
		memset(config->required_options, 0,
		    sizeof(config->required_options));
		parse_option_list(cfile, config->required_options);
		return;
	case TIMEOUT:
		parse_lease_time(cfile, &config->timeout);
		return;
	case RETRY:
		parse_lease_time(cfile, &config->retry_interval);
		return;
	case SELECT_TIMEOUT:
		parse_lease_time(cfile, &config->select_interval);
		return;
	case REBOOT:
		parse_lease_time(cfile, &config->reboot_timeout);
		return;
	case BACKOFF_CUTOFF:
		parse_lease_time(cfile, &config->backoff_cutoff);
		return;
	case INITIAL_INTERVAL:
		parse_lease_time(cfile, &config->initial_interval);
		return;
	case SCRIPT:
		config->script_name = parse_string(cfile);
		return;
	case INTERFACE:
		if (ip)
			parse_warn("nested interface declaration.");
		parse_interface_declaration(cfile, config);
		return;
	case LEASE:
		parse_client_lease_statement(cfile, 1);
		return;
	case ALIAS:
		parse_client_lease_statement(cfile, 2);
		return;
	case REJECT:
		parse_reject_statement(cfile, config);
		return;
	default:
		parse_warn("expecting a statement.");
		skip_to_semi(cfile);
		break;
	}
	token = next_token(&val, cfile);
	if (token != SEMI) {
		parse_warn("semicolon expected.");
		skip_to_semi(cfile);
	}
}
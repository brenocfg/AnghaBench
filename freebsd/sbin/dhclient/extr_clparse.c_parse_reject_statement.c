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
struct iaddr {int dummy; } ;
struct iaddrlist {struct iaddrlist* next; struct iaddr addr; } ;
struct client_config {struct iaddrlist* reject_list; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int COMMA ; 
 int SEMI ; 
 int /*<<< orphan*/  error (char*) ; 
 struct iaddrlist* malloc (int) ; 
 int next_token (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_ip_addr (int /*<<< orphan*/ *,struct iaddr*) ; 
 int /*<<< orphan*/  parse_warn (char*) ; 
 int /*<<< orphan*/  skip_to_semi (int /*<<< orphan*/ *) ; 

void
parse_reject_statement(FILE *cfile, struct client_config *config)
{
	int			 token;
	char			*val;
	struct iaddr		 addr;
	struct iaddrlist	*list;

	do {
		if (!parse_ip_addr(cfile, &addr)) {
			parse_warn("expecting IP address.");
			skip_to_semi(cfile);
			return;
		}

		list = malloc(sizeof(struct iaddrlist));
		if (!list)
			error("no memory for reject list!");

		list->addr = addr;
		list->next = config->reject_list;
		config->reject_list = list;

		token = next_token(&val, cfile);
	} while (token == COMMA);

	if (token != SEMI) {
		parse_warn("expecting semicolon.");
		skip_to_semi(cfile);
	}
}
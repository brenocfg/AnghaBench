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
struct ucl_parser {int dummy; } ;
struct conf {int dummy; } ;

/* Variables and functions */
 struct conf* conf ; 
 int /*<<< orphan*/  log_warn (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_parser_add_file (struct ucl_parser*,char const*) ; 
 int /*<<< orphan*/  ucl_parser_get_error (struct ucl_parser*) ; 
 int /*<<< orphan*/  ucl_parser_get_object (struct ucl_parser*) ; 
 struct ucl_parser* ucl_parser_new (int /*<<< orphan*/ ) ; 
 int uclparse_toplevel (int /*<<< orphan*/ ) ; 

int
uclparse_conf(struct conf *newconf, const char *path)
{
	struct ucl_parser *parser;
	int error; 

	conf = newconf;
	parser = ucl_parser_new(0);

	if (!ucl_parser_add_file(parser, path)) {
		log_warn("unable to parse configuration file %s: %s", path,
		    ucl_parser_get_error(parser));
		return (1);
	}

	error = uclparse_toplevel(ucl_parser_get_object(parser));

	return (error);
}
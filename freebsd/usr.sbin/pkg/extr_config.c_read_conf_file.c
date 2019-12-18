#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_1__ ucl_object_t ;
struct ucl_parser {int dummy; } ;
typedef  int /*<<< orphan*/  pkg_conf_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFFILE_PKG ; 
 int /*<<< orphan*/  CONFFILE_REPO ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ UCL_OBJECT ; 
 int /*<<< orphan*/  config_parse (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_repo_file (TYPE_1__*) ; 
 int /*<<< orphan*/  ucl_object_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  ucl_parser_add_file (struct ucl_parser*,char const*) ; 
 int /*<<< orphan*/  ucl_parser_free (struct ucl_parser*) ; 
 int /*<<< orphan*/  ucl_parser_get_error (struct ucl_parser*) ; 
 TYPE_1__* ucl_parser_get_object (struct ucl_parser*) ; 
 struct ucl_parser* ucl_parser_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
read_conf_file(const char *confpath, pkg_conf_file_t conftype)
{
	struct ucl_parser *p;
	ucl_object_t *obj = NULL;

	p = ucl_parser_new(0);

	if (!ucl_parser_add_file(p, confpath)) {
		if (errno != ENOENT)
			errx(EXIT_FAILURE, "Unable to parse configuration "
			    "file %s: %s", confpath, ucl_parser_get_error(p));
		ucl_parser_free(p);
		/* no configuration present */
		return (1);
	}

	obj = ucl_parser_get_object(p);
	if (obj->type != UCL_OBJECT) 
		warnx("Invalid configuration format, ignoring the "
		    "configuration file %s", confpath);
	else {
		if (conftype == CONFFILE_PKG)
			config_parse(obj, conftype);
		else if (conftype == CONFFILE_REPO)
			parse_repo_file(obj);
	}

	ucl_object_unref(obj);
	ucl_parser_free(p);

	return (0);
}
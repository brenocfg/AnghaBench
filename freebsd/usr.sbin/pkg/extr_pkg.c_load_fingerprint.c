#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ ucl_object_t ;
struct ucl_parser {int dummy; } ;
struct fingerprint {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 scalar_t__ UCL_OBJECT ; 
 struct fingerprint* parse_fingerprint (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  ucl_object_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  ucl_parser_add_file (struct ucl_parser*,char*) ; 
 int /*<<< orphan*/  ucl_parser_free (struct ucl_parser*) ; 
 int /*<<< orphan*/  ucl_parser_get_error (struct ucl_parser*) ; 
 TYPE_1__* ucl_parser_get_object (struct ucl_parser*) ; 
 struct ucl_parser* ucl_parser_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fingerprint *
load_fingerprint(const char *dir, const char *filename)
{
	ucl_object_t *obj = NULL;
	struct ucl_parser *p = NULL;
	struct fingerprint *f;
	char path[MAXPATHLEN];

	f = NULL;

	snprintf(path, MAXPATHLEN, "%s/%s", dir, filename);

	p = ucl_parser_new(0);
	if (!ucl_parser_add_file(p, path)) {
		warnx("%s: %s", path, ucl_parser_get_error(p));
		ucl_parser_free(p);
		return (NULL);
	}

	obj = ucl_parser_get_object(p);

	if (obj->type == UCL_OBJECT)
		f = parse_fingerprint(obj);

	if (f != NULL)
		f->name = strdup(filename);

	ucl_object_unref(obj);
	ucl_parser_free(p);

	return (f);
}
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
typedef  int /*<<< orphan*/  ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
struct ucl_parser {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_CONFIG_NAME ; 
 int asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 char* find_pf_device (int /*<<< orphan*/  const*) ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ucl_iterate_object (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 char* ucl_object_key (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ucl_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucl_parser_add_file (struct ucl_parser*,char const*) ; 
 int /*<<< orphan*/  ucl_parser_free (struct ucl_parser*) ; 
 char* ucl_parser_get_error (struct ucl_parser*) ; 
 int /*<<< orphan*/ * ucl_parser_get_object (struct ucl_parser*) ; 
 struct ucl_parser* ucl_parser_new (int /*<<< orphan*/ ) ; 

char *
find_device(const char *filename)
{
	char *device;
	const char *deviceName;
	ucl_object_iter_t it;
	struct ucl_parser *parser;
	ucl_object_t *top;
	const ucl_object_t *obj;
	const char *errmsg, *key;
	int error;

	device = NULL;
	deviceName = NULL;

	parser = ucl_parser_new(0);
	if (parser == NULL)
		err(1, "Could not allocate parser");

	if (!ucl_parser_add_file(parser, filename))
		err(1, "Could not open '%s' for reading", filename);

	errmsg = ucl_parser_get_error(parser);
	if (errmsg != NULL)
		errx(1, "Could not parse '%s': %s", filename, errmsg);

	top = ucl_parser_get_object (parser);
	it = NULL;
	while ((obj = ucl_iterate_object(top, &it, true)) != NULL) {
		key = ucl_object_key(obj);

		if (strcasecmp(key, PF_CONFIG_NAME) == 0) {
			deviceName = find_pf_device(obj);
			break;
		}
	}

	if (deviceName == NULL)
		errx(1, "Config file does not specify device");

	error = asprintf(&device, "/dev/iov/%s", deviceName);
	if (error < 0)
		err(1, "Could not allocate memory for device");

	ucl_object_unref(top);
	ucl_parser_free(parser);

	return (device);
}
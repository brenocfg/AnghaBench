#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;
struct ucl_parser {int /*<<< orphan*/  err; TYPE_1__* chunks; } ;
struct TYPE_7__ {unsigned int priority; } ;

/* Variables and functions */
 scalar_t__ UCL_INT ; 
 scalar_t__ UCL_OBJECT ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 unsigned int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  ucl_create_err (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__* ucl_object_iterate (TYPE_2__ const*,int /*<<< orphan*/ **,int) ; 
 unsigned int ucl_object_toint (TYPE_2__ const*) ; 
 int /*<<< orphan*/  ucl_strlcpy (char*,char const*,size_t) ; 

bool
ucl_priority_handler (const unsigned char *data, size_t len,
		const ucl_object_t *args, void* ud)
{
	struct ucl_parser *parser = ud;
	unsigned priority = 255;
	const ucl_object_t *param;
	bool found = false;
	char *value = NULL, *leftover = NULL;
	ucl_object_iter_t it = NULL;

	if (parser == NULL) {
		return false;
	}

	/* Process arguments */
	if (args != NULL && args->type == UCL_OBJECT) {
		while ((param = ucl_object_iterate (args, &it, true)) != NULL) {
			if (param->type == UCL_INT) {
				if (strncmp (param->key, "priority", param->keylen) == 0) {
					priority = ucl_object_toint (param);
					found = true;
				}
			}
		}
	}

	if (len > 0) {
		value = malloc(len + 1);
		ucl_strlcpy(value, (const char *)data, len + 1);
		priority = strtol(value, &leftover, 10);
		if (*leftover != '\0') {
			ucl_create_err (&parser->err, "Invalid priority value in macro: %s",
				value);
			free(value);
			return false;
		}
		free(value);
		found = true;
	}

	if (found == true) {
		parser->chunks->priority = priority;
		return true;
	}

	ucl_create_err (&parser->err, "Unable to parse priority macro");
	return false;
}
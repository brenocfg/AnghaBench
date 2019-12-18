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
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_object_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  ACPI_TYPE_STRING ; 

char *acpi_db_get_next_token(char *string,
			     char **next, acpi_object_type *return_type)
{
	char *start;
	u32 depth;
	acpi_object_type type = ACPI_TYPE_INTEGER;

	/* At end of buffer? */

	if (!string || !(*string)) {
		return (NULL);
	}

	/* Remove any spaces at the beginning */

	if (*string == ' ') {
		while (*string && (*string == ' ')) {
			string++;
		}

		if (!(*string)) {
			return (NULL);
		}
	}

	switch (*string) {
	case '"':

		/* This is a quoted string, scan until closing quote */

		string++;
		start = string;
		type = ACPI_TYPE_STRING;

		/* Find end of string */

		while (*string && (*string != '"')) {
			string++;
		}
		break;

	case '(':

		/* This is the start of a buffer, scan until closing paren */

		string++;
		start = string;
		type = ACPI_TYPE_BUFFER;

		/* Find end of buffer */

		while (*string && (*string != ')')) {
			string++;
		}
		break;

	case '[':

		/* This is the start of a package, scan until closing bracket */

		string++;
		depth = 1;
		start = string;
		type = ACPI_TYPE_PACKAGE;

		/* Find end of package (closing bracket) */

		while (*string) {

			/* Handle String package elements */

			if (*string == '"') {
				/* Find end of string */

				string++;
				while (*string && (*string != '"')) {
					string++;
				}
				if (!(*string)) {
					break;
				}
			} else if (*string == '[') {
				depth++;	/* A nested package declaration */
			} else if (*string == ']') {
				depth--;
				if (depth == 0) {	/* Found final package closing bracket */
					break;
				}
			}

			string++;
		}
		break;

	default:

		start = string;

		/* Find end of token */

		while (*string && (*string != ' ')) {
			string++;
		}
		break;
	}

	if (!(*string)) {
		*next = NULL;
	} else {
		*string = 0;
		*next = string + 1;
	}

	*return_type = type;
	return (start);
}
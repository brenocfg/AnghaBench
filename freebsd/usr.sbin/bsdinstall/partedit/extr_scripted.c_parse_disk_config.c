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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ isspace (char) ; 
 int part_config (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static
int parse_disk_config(char *input)
{
	char *ap;
	char *disk = NULL, *scheme = NULL, *partconfig = NULL;

	while (input != NULL && *input != 0) {
		if (isspace(*input)) {
			input++;
			continue;
		}

		switch(*input) {
		case '{':
			input++;
			partconfig = strchr(input, '}');
			if (partconfig == NULL) {
				fprintf(stderr, "Malformed partition setup "
				    "string: %s\n", input);
				return (1);
			}
			*partconfig = '\0';
			ap = partconfig+1;
			partconfig = input;
			input = ap;
			break;
		default:
			if (disk == NULL)
				disk = strsep(&input, " \t\n");
			else if (scheme == NULL)
				scheme = strsep(&input, " \t\n");
			else {
				fprintf(stderr, "Unknown directive: %s\n",
				    strsep(&input, " \t\n"));
				return (1);
			}
		}
	} while (input != NULL && *input != 0);

	if (disk != NULL)
		return (part_config(disk, scheme, partconfig));

	return (0);
}
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
struct auditfilter_module_list {int dummy; } ;
struct auditfilter_module {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int LINE_MAX ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (struct auditfilter_module_list*,struct auditfilter_module*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  am_list ; 
 int /*<<< orphan*/  auditfilter_module_list_free (struct auditfilter_module_list*) ; 
 struct auditfilter_module* auditfilter_module_parse (char const*,int,char*) ; 
 int errno ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
auditfilterd_conf_read(const char *filename, FILE *fp,
    struct auditfilter_module_list *list)
{
	int error, linenumber, syntaxerror;
	struct auditfilter_module *am;
	char buffer[LINE_MAX];

	syntaxerror = 0;
	linenumber = 0;
	while (!feof(fp) && !ferror(fp)) {
		if (fgets(buffer, LINE_MAX, fp) == NULL)
			break;
		linenumber++;
		if (buffer[0] == '#' || strlen(buffer) < 1)
			continue;
		buffer[strlen(buffer)-1] = '\0';
		am = auditfilter_module_parse(filename, linenumber, buffer);
		if (am == NULL) {
			syntaxerror = 1;
			break;
		}
		TAILQ_INSERT_HEAD(list, am, am_list);
	}

	/*
	 * File I/O error.
	 */
	if (ferror(fp)) {
		error = errno;
		auditfilter_module_list_free(list);
		errno = error;
		return (-1);
	}

	/*
	 * Syntax error.
	 */
	if (syntaxerror) {
		auditfilter_module_list_free(list);
		errno = EINVAL;
		return (-1);
	}
	return (0);
}
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
struct lafe_line_reader {int nullSeparator; int buff_length; int /*<<< orphan*/ * buff; int /*<<< orphan*/  buff_end; int /*<<< orphan*/  line_end; int /*<<< orphan*/  line_start; int /*<<< orphan*/ * f; int /*<<< orphan*/  pathname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct lafe_line_reader* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

struct lafe_line_reader *
lafe_line_reader(const char *pathname, int nullSeparator)
{
	struct lafe_line_reader *lr;

	lr = calloc(1, sizeof(*lr));
	if (lr == NULL)
		lafe_errc(1, ENOMEM, "Can't open %s", pathname);

	lr->nullSeparator = nullSeparator;
	lr->pathname = strdup(pathname);

	if (strcmp(pathname, "-") == 0)
		lr->f = stdin;
	else
		lr->f = fopen(pathname, "r");
	if (lr->f == NULL)
		lafe_errc(1, errno, "Couldn't open %s", pathname);
	lr->buff_length = 8192;
	lr->line_start = lr->line_end = lr->buff_end = lr->buff = NULL;

	return (lr);
}
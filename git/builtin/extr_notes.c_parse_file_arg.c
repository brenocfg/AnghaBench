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
struct option {struct note_data* value; } ;
struct TYPE_5__ {scalar_t__ len; } ;
struct note_data {int given; TYPE_1__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strbuf_addch (TYPE_1__*,char) ; 
 scalar_t__ strbuf_read (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strbuf_read_file (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_stripspace (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int parse_file_arg(const struct option *opt, const char *arg, int unset)
{
	struct note_data *d = opt->value;

	BUG_ON_OPT_NEG(unset);

	if (d->buf.len)
		strbuf_addch(&d->buf, '\n');
	if (!strcmp(arg, "-")) {
		if (strbuf_read(&d->buf, 0, 1024) < 0)
			die_errno(_("cannot read '%s'"), arg);
	} else if (strbuf_read_file(&d->buf, arg, 1024) < 0)
		die_errno(_("could not open or read '%s'"), arg);
	strbuf_stripspace(&d->buf, 0);

	d->given = 1;
	return 0;
}
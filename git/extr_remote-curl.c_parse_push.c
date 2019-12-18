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
struct strbuf {int /*<<< orphan*/ * buf; } ;
struct argv_array {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 scalar_t__ EOF ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ starts_with (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void parse_push(struct strbuf *buf)
{
	struct argv_array specs = ARGV_ARRAY_INIT;
	int ret;

	do {
		if (starts_with(buf->buf, "push "))
			argv_array_push(&specs, buf->buf + 5);
		else
			die(_("http transport does not support %s"), buf->buf);

		strbuf_reset(buf);
		if (strbuf_getline_lf(buf, stdin) == EOF)
			goto free_specs;
		if (!*buf->buf)
			break;
	} while (1);

	ret = push(specs.argc, specs.argv);
	printf("\n");
	fflush(stdout);

	if (ret)
		exit(128); /* error already reported */

 free_specs:
	argv_array_clear(&specs);
}
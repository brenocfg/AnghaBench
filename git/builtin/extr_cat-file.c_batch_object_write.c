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
struct strbuf {char* buf; int len; } ;
struct expand_data {int /*<<< orphan*/  oid; int /*<<< orphan*/  info; int /*<<< orphan*/  skip_object_info; } ;
struct batch_options {scalar_t__ print_contents; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJECT_INFO_LOOKUP_REPLACE ; 
 int /*<<< orphan*/  batch_write (struct batch_options*,char*,int) ; 
 int /*<<< orphan*/  expand_format ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ oid_object_info_extended (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_object_or_die (struct batch_options*,struct expand_data*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_expand (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct expand_data*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void batch_object_write(const char *obj_name,
			       struct strbuf *scratch,
			       struct batch_options *opt,
			       struct expand_data *data)
{
	if (!data->skip_object_info &&
	    oid_object_info_extended(the_repository, &data->oid, &data->info,
				     OBJECT_INFO_LOOKUP_REPLACE) < 0) {
		printf("%s missing\n",
		       obj_name ? obj_name : oid_to_hex(&data->oid));
		fflush(stdout);
		return;
	}

	strbuf_reset(scratch);
	strbuf_expand(scratch, opt->format, expand_format, data);
	strbuf_addch(scratch, '\n');
	batch_write(opt, scratch->buf, scratch->len);

	if (opt->print_contents) {
		print_object_or_die(opt, data);
		batch_write(opt, "\n", 1);
	}
}
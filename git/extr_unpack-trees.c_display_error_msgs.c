#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct unpack_trees_options {struct string_list* unpack_rejects; } ;
struct string_list {int nr; TYPE_1__* items; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRORMSG (struct unpack_trees_options*,int) ; 
 int NB_UNPACK_TREES_ERROR_TYPES ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  super_prefixed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void display_error_msgs(struct unpack_trees_options *o)
{
	int e, i;
	int something_displayed = 0;
	for (e = 0; e < NB_UNPACK_TREES_ERROR_TYPES; e++) {
		struct string_list *rejects = &o->unpack_rejects[e];
		if (rejects->nr > 0) {
			struct strbuf path = STRBUF_INIT;
			something_displayed = 1;
			for (i = 0; i < rejects->nr; i++)
				strbuf_addf(&path, "\t%s\n", rejects->items[i].string);
			error(ERRORMSG(o, e), super_prefixed(path.buf));
			strbuf_release(&path);
		}
		string_list_clear(rejects, 0);
	}
	if (something_displayed)
		fprintf(stderr, _("Aborting\n"));
}
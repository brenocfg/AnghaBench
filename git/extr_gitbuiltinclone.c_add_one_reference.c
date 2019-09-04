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
struct string_list_item {char* string; } ;
struct strbuf {char* buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  add_to_alternates_file (char*) ; 
 char* compute_alternate_path (char*,struct strbuf*) ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int add_one_reference(struct string_list_item *item, void *cb_data)
{
	struct strbuf err = STRBUF_INIT;
	int *required = cb_data;
	char *ref_git = compute_alternate_path(item->string, &err);

	if (!ref_git) {
		if (*required)
			die("%s", err.buf);
		else
			fprintf(stderr,
				_("info: Could not add alternate for '%s': %s\n"),
				item->string, err.buf);
	} else {
		struct strbuf sb = STRBUF_INIT;
		strbuf_addf(&sb, "%s/objects", ref_git);
		add_to_alternates_file(sb.buf);
		strbuf_release(&sb);
	}

	strbuf_release(&err);
	free(ref_git);
	return 0;
}
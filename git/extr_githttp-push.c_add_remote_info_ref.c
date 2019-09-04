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
struct strbuf {int dummy; } ;
struct remote_ls_ctx {char* dentry_name; scalar_t__ userData; } ;
struct ref {int /*<<< orphan*/  old_oid; } ;
struct object {scalar_t__ type; int /*<<< orphan*/  oid; } ;
struct TYPE_2__ {char* url; } ;

/* Variables and functions */
 scalar_t__ OBJ_TAG ; 
 int aborted ; 
 struct ref* alloc_ref (char*) ; 
 struct object* deref_tag (int /*<<< orphan*/ ,struct object*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  free (struct ref*) ; 
 scalar_t__ http_fetch_ref (char*,struct ref*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 struct object* parse_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* repo ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*,char*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void add_remote_info_ref(struct remote_ls_ctx *ls)
{
	struct strbuf *buf = (struct strbuf *)ls->userData;
	struct object *o;
	struct ref *ref;

	ref = alloc_ref(ls->dentry_name);

	if (http_fetch_ref(repo->url, ref) != 0) {
		fprintf(stderr,
			"Unable to fetch ref %s from %s\n",
			ls->dentry_name, repo->url);
		aborted = 1;
		free(ref);
		return;
	}

	o = parse_object(the_repository, &ref->old_oid);
	if (!o) {
		fprintf(stderr,
			"Unable to parse object %s for remote ref %s\n",
			oid_to_hex(&ref->old_oid), ls->dentry_name);
		aborted = 1;
		free(ref);
		return;
	}

	strbuf_addf(buf, "%s\t%s\n",
		    oid_to_hex(&ref->old_oid), ls->dentry_name);

	if (o->type == OBJ_TAG) {
		o = deref_tag(the_repository, o, ls->dentry_name, 0);
		if (o)
			strbuf_addf(buf, "%s\t%s^{}\n",
				    oid_to_hex(&o->oid), ls->dentry_name);
	}
	free(ref);
}
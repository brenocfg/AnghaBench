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
struct strbuf {int dummy; } ;
struct remote {int dummy; } ;
struct ref {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ deleterefs ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 struct ref* get_local_heads () ; 
 char* map_refspec (char const*,struct remote*,struct ref*) ; 
 int /*<<< orphan*/  refspec_append (int /*<<< orphan*/ *,char const*) ; 
 struct remote* remote_get (char const*) ; 
 int /*<<< orphan*/  rs ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static void set_refspecs(const char **refs, int nr, const char *repo)
{
	struct remote *remote = NULL;
	struct ref *local_refs = NULL;
	int i;

	for (i = 0; i < nr; i++) {
		const char *ref = refs[i];
		if (!strcmp("tag", ref)) {
			struct strbuf tagref = STRBUF_INIT;
			if (nr <= ++i)
				die(_("tag shorthand without <tag>"));
			ref = refs[i];
			if (deleterefs)
				strbuf_addf(&tagref, ":refs/tags/%s", ref);
			else
				strbuf_addf(&tagref, "refs/tags/%s", ref);
			ref = strbuf_detach(&tagref, NULL);
		} else if (deleterefs) {
			struct strbuf delref = STRBUF_INIT;
			if (strchr(ref, ':'))
				die(_("--delete only accepts plain target ref names"));
			strbuf_addf(&delref, ":%s", ref);
			ref = strbuf_detach(&delref, NULL);
		} else if (!strchr(ref, ':')) {
			if (!remote) {
				/* lazily grab remote and local_refs */
				remote = remote_get(repo);
				local_refs = get_local_heads();
			}
			ref = map_refspec(ref, remote, local_refs);
		}
		refspec_append(&rs, ref);
	}
}
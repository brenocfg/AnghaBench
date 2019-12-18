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
struct submodule_alternate_setup {int error_mode; int /*<<< orphan*/  submodule_name; int /*<<< orphan*/  reference; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct object_directory {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
#define  SUBMODULE_ALTERNATE_ERROR_DIE 130 
#define  SUBMODULE_ALTERNATE_ERROR_IGNORE 129 
#define  SUBMODULE_ALTERNATE_ERROR_INFO 128 
 int /*<<< orphan*/  _ (char*) ; 
 char* compute_alternate_path (int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strip_suffix (int /*<<< orphan*/ ,char*,size_t*) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_possible_reference_from_superproject(
		struct object_directory *odb, void *sas_cb)
{
	struct submodule_alternate_setup *sas = sas_cb;
	size_t len;

	/*
	 * If the alternate object store is another repository, try the
	 * standard layout with .git/(modules/<name>)+/objects
	 */
	if (strip_suffix(odb->path, "/objects", &len)) {
		char *sm_alternate;
		struct strbuf sb = STRBUF_INIT;
		struct strbuf err = STRBUF_INIT;
		strbuf_add(&sb, odb->path, len);

		/*
		 * We need to end the new path with '/' to mark it as a dir,
		 * otherwise a submodule name containing '/' will be broken
		 * as the last part of a missing submodule reference would
		 * be taken as a file name.
		 */
		strbuf_addf(&sb, "/modules/%s/", sas->submodule_name);

		sm_alternate = compute_alternate_path(sb.buf, &err);
		if (sm_alternate) {
			string_list_append(sas->reference, xstrdup(sb.buf));
			free(sm_alternate);
		} else {
			switch (sas->error_mode) {
			case SUBMODULE_ALTERNATE_ERROR_DIE:
				die(_("submodule '%s' cannot add alternate: %s"),
				    sas->submodule_name, err.buf);
			case SUBMODULE_ALTERNATE_ERROR_INFO:
				fprintf_ln(stderr, _("submodule '%s' cannot add alternate: %s"),
					sas->submodule_name, err.buf);
			case SUBMODULE_ALTERNATE_ERROR_IGNORE:
				; /* nothing */
			}
		}
		strbuf_release(&sb);
	}

	return 0;
}
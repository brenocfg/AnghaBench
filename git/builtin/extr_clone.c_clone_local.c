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
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  add_to_alternates_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_or_link_directory (struct strbuf*,struct strbuf*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_common_dir (struct strbuf*,char const*) ; 
 scalar_t__ option_shared ; 
 scalar_t__ option_verbosity ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void clone_local(const char *src_repo, const char *dest_repo)
{
	if (option_shared) {
		struct strbuf alt = STRBUF_INIT;
		get_common_dir(&alt, src_repo);
		strbuf_addstr(&alt, "/objects");
		add_to_alternates_file(alt.buf);
		strbuf_release(&alt);
	} else {
		struct strbuf src = STRBUF_INIT;
		struct strbuf dest = STRBUF_INIT;
		get_common_dir(&src, src_repo);
		get_common_dir(&dest, dest_repo);
		strbuf_addstr(&src, "/objects");
		strbuf_addstr(&dest, "/objects");
		copy_or_link_directory(&src, &dest, src_repo);
		strbuf_release(&src);
		strbuf_release(&dest);
	}

	if (0 <= option_verbosity)
		fprintf(stderr, _("done.\n"));
}
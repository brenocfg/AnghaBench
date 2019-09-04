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
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int /*<<< orphan*/  R_OK ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_set (char*,char*) ; 
 int /*<<< orphan*/  git_path_buf (struct strbuf*,char*,char const*) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int precomposed_unicode ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ unlink (int /*<<< orphan*/ ) ; 

void probe_utf8_pathname_composition(void)
{
	struct strbuf path = STRBUF_INIT;
	static const char *auml_nfc = "\xc3\xa4";
	static const char *auml_nfd = "\x61\xcc\x88";
	int output_fd;
	if (precomposed_unicode != -1)
		return; /* We found it defined in the global config, respect it */
	git_path_buf(&path, "%s", auml_nfc);
	output_fd = open(path.buf, O_CREAT|O_EXCL|O_RDWR, 0600);
	if (output_fd >= 0) {
		close(output_fd);
		git_path_buf(&path, "%s", auml_nfd);
		precomposed_unicode = access(path.buf, R_OK) ? 0 : 1;
		git_config_set("core.precomposeunicode",
			       precomposed_unicode ? "true" : "false");
		git_path_buf(&path, "%s", auml_nfc);
		if (unlink(path.buf))
			die_errno(_("failed to unlink '%s'"), path.buf);
	}
	strbuf_release(&path);
}
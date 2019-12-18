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

/* Variables and functions */
 scalar_t__ EEXIST ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ close (int) ; 
 char* derive_filename (char const*,char const*,struct strbuf*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*,char const*) ; 
 scalar_t__ errno ; 
 int odb_pack_keep (char const*) ; 
 char* odb_pack_name (struct strbuf*,unsigned char const*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  write_or_die (int,char const*,int) ; 

__attribute__((used)) static void write_special_file(const char *suffix, const char *msg,
			       const char *pack_name, const unsigned char *hash,
			       const char **report)
{
	struct strbuf name_buf = STRBUF_INIT;
	const char *filename;
	int fd;
	int msg_len = strlen(msg);

	if (pack_name)
		filename = derive_filename(pack_name, suffix, &name_buf);
	else
		filename = odb_pack_name(&name_buf, hash, suffix);

	fd = odb_pack_keep(filename);
	if (fd < 0) {
		if (errno != EEXIST)
			die_errno(_("cannot write %s file '%s'"),
				  suffix, filename);
	} else {
		if (msg_len > 0) {
			write_or_die(fd, msg, msg_len);
			write_or_die(fd, "\n", 1);
		}
		if (close(fd) != 0)
			die_errno(_("cannot close written %s file '%s'"),
				  suffix, filename);
		if (report)
			*report = suffix;
	}
	strbuf_release(&name_buf);
}
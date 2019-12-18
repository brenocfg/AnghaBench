#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int length; int /*<<< orphan*/  s; } ;
struct shar {scalar_t__ outpos; TYPE_1__ work; int /*<<< orphan*/ * entry; int /*<<< orphan*/  end_of_line; scalar_t__ has_data; int /*<<< orphan*/  outbuff; scalar_t__ dump; } ;
struct archive_write {scalar_t__ format_data; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int __archive_write_output (struct archive_write*,int /*<<< orphan*/ ,int) ; 
 char* archive_entry_fflags_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_entry_free (int /*<<< orphan*/ *) ; 
 char* archive_entry_gname (int /*<<< orphan*/ *) ; 
 int archive_entry_mode (int /*<<< orphan*/ *) ; 
 char const* archive_entry_pathname (int /*<<< orphan*/ *) ; 
 char* archive_entry_uname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_strappend_char (TYPE_1__*,char) ; 
 int /*<<< orphan*/  archive_strcat (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  archive_string_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  archive_string_sprintf (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  shar_quote (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  uuencode_line (struct archive_write*,struct shar*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
archive_write_shar_finish_entry(struct archive_write *a)
{
	const char *g, *p, *u;
	struct shar *shar;
	int ret;

	shar = (struct shar *)a->format_data;
	if (shar->entry == NULL)
		return (0);

	if (shar->dump) {
		/* Finish uuencoded data. */
		if (shar->has_data) {
			if (shar->outpos > 0)
				uuencode_line(a, shar, shar->outbuff,
				    shar->outpos);
			archive_strcat(&shar->work, "`\nend\n");
			archive_strcat(&shar->work, "SHAR_END\n");
		}
		/* Restore file mode, owner, flags. */
		/*
		 * TODO: Don't immediately restore mode for
		 * directories; defer that to end of script.
		 */
		archive_string_sprintf(&shar->work, "chmod %o ",
		    (unsigned int)(archive_entry_mode(shar->entry) & 07777));
		shar_quote(&shar->work, archive_entry_pathname(shar->entry), 1);
		archive_strcat(&shar->work, "\n");

		u = archive_entry_uname(shar->entry);
		g = archive_entry_gname(shar->entry);
		if (u != NULL || g != NULL) {
			archive_strcat(&shar->work, "chown ");
			if (u != NULL)
				shar_quote(&shar->work, u, 1);
			if (g != NULL) {
				archive_strcat(&shar->work, ":");
				shar_quote(&shar->work, g, 1);
			}
			archive_strcat(&shar->work, " ");
			shar_quote(&shar->work,
			    archive_entry_pathname(shar->entry), 1);
			archive_strcat(&shar->work, "\n");
		}

		if ((p = archive_entry_fflags_text(shar->entry)) != NULL) {
			archive_string_sprintf(&shar->work, "chflags %s ", p);
			shar_quote(&shar->work,
			    archive_entry_pathname(shar->entry), 1);
			archive_strcat(&shar->work, "\n");
		}

		/* TODO: restore ACLs */

	} else {
		if (shar->has_data) {
			/* Finish sed-encoded data:  ensure last line ends. */
			if (!shar->end_of_line)
				archive_strappend_char(&shar->work, '\n');
			archive_strcat(&shar->work, "SHAR_END\n");
		}
	}

	archive_entry_free(shar->entry);
	shar->entry = NULL;

	if (shar->work.length < 65536)
		return (ARCHIVE_OK);

	ret = __archive_write_output(a, shar->work.s, shar->work.length);
	if (ret != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	archive_string_empty(&shar->work);

	return (ARCHIVE_OK);
}
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
struct warc_s {int dummy; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ENOMEM ; 
 int __archive_read_register_format (struct archive_read*,struct warc_s*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _warc_bid ; 
 int /*<<< orphan*/  _warc_cleanup ; 
 int /*<<< orphan*/  _warc_rdhdr ; 
 int /*<<< orphan*/  _warc_read ; 
 int /*<<< orphan*/  _warc_skip ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct warc_s* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct warc_s*) ; 

int
archive_read_support_format_warc(struct archive *_a)
{
	struct archive_read *a = (struct archive_read *)_a;
	struct warc_s *w;
	int r;

	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_format_warc");

	if ((w = calloc(1, sizeof(*w))) == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate warc data");
		return (ARCHIVE_FATAL);
	}

	r = __archive_read_register_format(
		a, w, "warc",
		_warc_bid, NULL, _warc_rdhdr, _warc_read,
		_warc_skip, NULL, _warc_cleanup, NULL, NULL);

	if (r != ARCHIVE_OK) {
		free(w);
		return (r);
	}
	return (ARCHIVE_OK);
}
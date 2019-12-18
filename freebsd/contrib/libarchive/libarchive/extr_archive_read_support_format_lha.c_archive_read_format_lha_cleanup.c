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
struct lha {int /*<<< orphan*/  ws; int /*<<< orphan*/  gname; int /*<<< orphan*/  uname; int /*<<< orphan*/  filename; int /*<<< orphan*/  dirname; int /*<<< orphan*/  strm; } ;
struct archive_read {TYPE_1__* format; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_wstring_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct lha*) ; 
 int /*<<< orphan*/  lzh_decode_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
archive_read_format_lha_cleanup(struct archive_read *a)
{
	struct lha *lha = (struct lha *)(a->format->data);

	lzh_decode_free(&(lha->strm));
	archive_string_free(&(lha->dirname));
	archive_string_free(&(lha->filename));
	archive_string_free(&(lha->uname));
	archive_string_free(&(lha->gname));
	archive_wstring_free(&(lha->ws));
	free(lha);
	(a->format->data) = NULL;
	return (ARCHIVE_OK);
}
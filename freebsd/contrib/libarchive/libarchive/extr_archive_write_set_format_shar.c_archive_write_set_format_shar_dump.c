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
struct shar {int dump; } ;
struct TYPE_2__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_write {TYPE_1__ archive; int /*<<< orphan*/  format_write_data; scalar_t__ format_data; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_FORMAT_SHAR_DUMP ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_write_set_format_shar (TYPE_1__*) ; 
 int /*<<< orphan*/  archive_write_shar_data_uuencode ; 

int
archive_write_set_format_shar_dump(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct shar *shar;

	archive_write_set_format_shar(&a->archive);
	shar = (struct shar *)a->format_data;
	shar->dump = 1;
	a->format_write_data = archive_write_shar_data_uuencode;
	a->archive.archive_format = ARCHIVE_FORMAT_SHAR_DUMP;
	a->archive.archive_format_name = "shar dump";
	return (ARCHIVE_OK);
}
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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ Z1_opt ; 
 int /*<<< orphan*/  ac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 char* archive_entry_pathname (struct archive_entry*) ; 
 scalar_t__ archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_data_skip (struct archive*) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int v_opt ; 
 scalar_t__* y_str ; 
 int /*<<< orphan*/  zipinfo_mode ; 

__attribute__((used)) static void
list(struct archive *a, struct archive_entry *e)
{
	char buf[20];
	time_t mtime;
	struct tm *tm;

	mtime = archive_entry_mtime(e);
	tm = localtime(&mtime);
	if (*y_str)
		strftime(buf, sizeof(buf), "%m-%d-%G %R", tm);
	else
		strftime(buf, sizeof(buf), "%m-%d-%g %R", tm);

	if (!zipinfo_mode) {
		if (v_opt == 1) {
			printf(" %8ju  %s   %s\n",
			    (uintmax_t)archive_entry_size(e),
			    buf, archive_entry_pathname(e));
		} else if (v_opt == 2) {
			printf("%8ju  Stored  %7ju   0%%  %s  %08x  %s\n",
			    (uintmax_t)archive_entry_size(e),
			    (uintmax_t)archive_entry_size(e),
			    buf,
			    0U,
			    archive_entry_pathname(e));
		}
	} else {
		if (Z1_opt)
			printf("%s\n",archive_entry_pathname(e));
	}
	ac(archive_read_data_skip(a));
}
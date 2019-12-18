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
struct archiver_args {int /*<<< orphan*/  commit_oid; int /*<<< orphan*/  time; } ;
struct archiver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_zip_config ; 
 int /*<<< orphan*/  dos_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 
 int write_archive_entries (struct archiver_args*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_zip_entry ; 
 int /*<<< orphan*/  write_zip_trailer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_date ; 
 int /*<<< orphan*/  zip_dir ; 
 int /*<<< orphan*/  zip_time ; 

__attribute__((used)) static int write_zip_archive(const struct archiver *ar,
			     struct archiver_args *args)
{
	int err;

	git_config(archive_zip_config, NULL);

	dos_time(&args->time, &zip_date, &zip_time);

	strbuf_init(&zip_dir, 0);

	err = write_archive_entries(args, write_zip_entry);
	if (!err)
		write_zip_trailer(args->commit_oid);

	strbuf_release(&zip_dir);

	return err;
}
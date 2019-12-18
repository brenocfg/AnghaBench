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
struct archiver_args {int dummy; } ;
struct archiver {int dummy; } ;

/* Variables and functions */
 int write_archive_entries (struct archiver_args*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_global_extended_header (struct archiver_args*) ; 
 int /*<<< orphan*/  write_tar_entry ; 
 int /*<<< orphan*/  write_trailer () ; 

__attribute__((used)) static int write_tar_archive(const struct archiver *ar,
			     struct archiver_args *args)
{
	int err = 0;

	write_global_extended_header(args);
	err = write_archive_entries(args, write_tar_entry);
	if (!err)
		write_trailer();
	return err;
}
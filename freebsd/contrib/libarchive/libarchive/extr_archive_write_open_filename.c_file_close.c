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
struct write_file_data {scalar_t__ fd; int /*<<< orphan*/  filename; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_mstring_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (struct write_file_data*) ; 

__attribute__((used)) static int
file_close(struct archive *a, void *client_data)
{
	struct write_file_data	*mine = (struct write_file_data *)client_data;

	(void)a; /* UNUSED */

	if (mine->fd >= 0)
		close(mine->fd);

	archive_mstring_clean(&mine->filename);
	free(mine);
	return (ARCHIVE_OK);
}
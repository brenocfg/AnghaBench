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
struct archive_write {int /*<<< orphan*/  archive; scalar_t__ format_data; } ;
struct TYPE_2__ {struct _7zip* props; } ;
struct _7zip {scalar_t__ temp_fd; TYPE_1__ coder; int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  compression_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_free_register (struct _7zip*) ; 
 int /*<<< orphan*/  free (struct _7zip*) ; 

__attribute__((used)) static int
_7z_free(struct archive_write *a)
{
	struct _7zip *zip = (struct _7zip *)a->format_data;

	/* Close the temporary file. */
	if (zip->temp_fd >= 0)
		close(zip->temp_fd);

	file_free_register(zip);
	compression_end(&(a->archive), &(zip->stream));
	free(zip->coder.props);
	free(zip);

	return (ARCHIVE_OK);
}
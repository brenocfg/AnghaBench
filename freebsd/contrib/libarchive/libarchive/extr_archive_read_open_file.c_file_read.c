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
struct read_FILE_data {void* buffer; size_t block_size; int /*<<< orphan*/  f; } ;
struct archive {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 size_t fread (void*,int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
file_read(struct archive *a, void *client_data, const void **buff)
{
	struct read_FILE_data *mine = (struct read_FILE_data *)client_data;
	size_t bytes_read;

	*buff = mine->buffer;
	bytes_read = fread(mine->buffer, 1, mine->block_size, mine->f);
	if (bytes_read < mine->block_size && ferror(mine->f)) {
		archive_set_error(a, errno, "Error reading file");
	}
	return (bytes_read);
}
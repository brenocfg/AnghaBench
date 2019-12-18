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
struct read_fd_data {void* buffer; int /*<<< orphan*/  fd; int /*<<< orphan*/  block_size; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ read (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
file_read(struct archive *a, void *client_data, const void **buff)
{
	struct read_fd_data *mine = (struct read_fd_data *)client_data;
	ssize_t bytes_read;

	*buff = mine->buffer;
	for (;;) {
		bytes_read = read(mine->fd, mine->buffer, mine->block_size);
		if (bytes_read < 0) {
			if (errno == EINTR)
				continue;
			archive_set_error(a, errno, "Error reading fd %d",
			    mine->fd);
		}
		return (bytes_read);
	}
}
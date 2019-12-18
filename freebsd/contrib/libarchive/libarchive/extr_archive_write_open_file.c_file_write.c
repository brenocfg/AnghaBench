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
struct write_FILE_data {int /*<<< orphan*/  f; } ;
struct archive {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,scalar_t__,char*) ; 
 scalar_t__ errno ; 
 size_t fwrite (void const*,int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
file_write(struct archive *a, void *client_data, const void *buff, size_t length)
{
	struct write_FILE_data	*mine;
	size_t	bytesWritten;

	mine = client_data;
	for (;;) {
		bytesWritten = fwrite(buff, 1, length, mine->f);
		if (bytesWritten <= 0) {
			if (errno == EINTR)
				continue;
			archive_set_error(a, errno, "Write error");
			return (-1);
		}
		return (bytesWritten);
	}
}
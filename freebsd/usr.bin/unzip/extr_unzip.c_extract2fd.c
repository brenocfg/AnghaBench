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
struct archive {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ BYTE_IS_BINARY (unsigned char) ; 
 int STDOUT_FILENO ; 
 int a_opt ; 
 int /*<<< orphan*/  ac (scalar_t__) ; 
 scalar_t__ archive_read_data (struct archive*,char*,int) ; 
 char* buffer ; 
 scalar_t__ check_binary (char*,scalar_t__) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spinner ; 
 scalar_t__ tty ; 
 int /*<<< orphan*/  warningx (char*,char*) ; 
 int write (int,...) ; 

__attribute__((used)) static int
extract2fd(struct archive *a, char *pathname, int fd)
{
	int cr, text, warn;
	ssize_t len;
	unsigned char *p, *q, *end;

	text = a_opt;
	warn = 0;
	cr = 0;

	/* loop over file contents and write to fd */
	for (int n = 0; ; n++) {
		if (fd != STDOUT_FILENO)
			if (tty && (n % 4) == 0)
				info(" %c\b\b", spinner[(n / 4) % sizeof spinner]);

		len = archive_read_data(a, buffer, sizeof buffer);

		if (len < 0)
			ac(len);

		/* left over CR from previous buffer */
		if (a_opt && cr) {
			if (len == 0 || buffer[0] != '\n')
				if (write(fd, "\r", 1) != 1)
					error("write('%s')", pathname);
			cr = 0;
		}

		/* EOF */
		if (len == 0)
			break;
		end = buffer + len;

		/*
		 * Detect whether this is a text file.  The correct way to
		 * do this is to check the least significant bit of the
		 * "internal file attributes" field of the corresponding
		 * file header in the central directory, but libarchive
		 * does not provide access to this field, so we have to
		 * guess by looking for non-ASCII characters in the
		 * buffer.  Hopefully we won't guess wrong.  If we do
		 * guess wrong, we print a warning message later.
		 */
		if (a_opt && n == 0) {
			if (check_binary(buffer, len))
				text = 0;
		}

		/* simple case */
		if (!a_opt || !text) {
			if (write(fd, buffer, len) != len)
				error("write('%s')", pathname);
			continue;
		}

		/* hard case: convert \r\n to \n (sigh...) */
		for (p = buffer; p < end; p = q + 1) {
			for (q = p; q < end; q++) {
				if (!warn && BYTE_IS_BINARY(*q)) {
					warningx("%s may be corrupted due"
					    " to weak text file detection"
					    " heuristic", pathname);
					warn = 1;
				}
				if (q[0] != '\r')
					continue;
				if (&q[1] == end) {
					cr = 1;
					break;
				}
				if (q[1] == '\n')
					break;
			}
			if (write(fd, p, q - p) != q - p)
				error("write('%s')", pathname);
		}
	}

	return text;
}
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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  token_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int MAX_AUDIT_RECORD_SIZE ; 
 scalar_t__ au_close_buffer (int,short,int /*<<< orphan*/ *,size_t*) ; 
 int au_open () ; 
 scalar_t__ au_write (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int open_file (char const*,char const*) ; 
 int /*<<< orphan*/  write_file (int,int /*<<< orphan*/ *,size_t,char const*) ; 

__attribute__((used)) static void
write_record(const char *directory, const char *filename, token_t *tok,
    short event)
{
	u_char buffer[MAX_AUDIT_RECORD_SIZE];
	size_t buflen;
	int au, fd;

	au = au_open();
	if (au < 0)
		err(EX_UNAVAILABLE, "au_open");
	if (au_write(au, tok) < 0)
		err(EX_UNAVAILABLE, "au_write");
	buflen = MAX_AUDIT_RECORD_SIZE;
	if (au_close_buffer(au, event, buffer, &buflen) < 0)
		err(EX_UNAVAILABLE, "au_close_buffer");
	fd = open_file(directory, filename);
	write_file(fd, buffer, buflen, filename);
	close(fd);
}
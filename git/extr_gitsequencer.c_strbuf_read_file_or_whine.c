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
struct strbuf {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ error (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ error_errno (int /*<<< orphan*/ ,char const*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strbuf_read (struct strbuf*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t strbuf_read_file_or_whine(struct strbuf *sb, const char *path)
{
	int fd;
	ssize_t len;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return error_errno(_("could not open '%s'"), path);
	len = strbuf_read(sb, fd, 0);
	close(fd);
	if (len < 0)
		return error(_("could not read '%s'."), path);
	return len;
}
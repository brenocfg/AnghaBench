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
struct stat {int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_size; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  content_length ; 
 int /*<<< orphan*/  content_type ; 
 int /*<<< orphan*/  die_errno (char*,char*) ; 
 int /*<<< orphan*/  end_headers (struct strbuf*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 char* git_pathdup (char*,char const*) ; 
 int /*<<< orphan*/  hdr_date (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdr_int (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdr_str (struct strbuf*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  last_modified ; 
 int /*<<< orphan*/  not_found (struct strbuf*,char*,char*,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_or_die (int,char*,scalar_t__) ; 
 char* xmalloc (size_t) ; 
 scalar_t__ xread (int,char*,size_t) ; 

__attribute__((used)) static void send_local_file(struct strbuf *hdr, const char *the_type,
				const char *name)
{
	char *p = git_pathdup("%s", name);
	size_t buf_alloc = 8192;
	char *buf = xmalloc(buf_alloc);
	int fd;
	struct stat sb;

	fd = open(p, O_RDONLY);
	if (fd < 0)
		not_found(hdr, "Cannot open '%s': %s", p, strerror(errno));
	if (fstat(fd, &sb) < 0)
		die_errno("Cannot stat '%s'", p);

	hdr_int(hdr, content_length, sb.st_size);
	hdr_str(hdr, content_type, the_type);
	hdr_date(hdr, last_modified, sb.st_mtime);
	end_headers(hdr);

	for (;;) {
		ssize_t n = xread(fd, buf, buf_alloc);
		if (n < 0)
			die_errno("Cannot read '%s'", p);
		if (!n)
			break;
		write_or_die(1, buf, n);
	}
	close(fd);
	free(buf);
	free(p);
}
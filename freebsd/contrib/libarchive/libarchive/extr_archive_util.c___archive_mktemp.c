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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct archive_string {char* s; int length; } ;
typedef  int /*<<< orphan*/  num ;

/* Variables and functions */
 scalar_t__ ARCHIVE_OK ; 
 scalar_t__ EEXIST ; 
 scalar_t__ ENOTDIR ; 
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __archive_ensure_cloexec_flag (int) ; 
 int /*<<< orphan*/  archive_random (char*,int) ; 
 int /*<<< orphan*/  archive_strcat (struct archive_string*,char*) ; 
 int /*<<< orphan*/  archive_strcpy (struct archive_string*,char const*) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 int archive_strlen (struct archive_string*) ; 
 scalar_t__ errno ; 
 scalar_t__ get_tempdir (struct archive_string*) ; 
 scalar_t__ la_stat (char*,struct stat*) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int
__archive_mktemp(const char *tmpdir)
{
        static const char num[] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
		'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
		'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
		'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
		'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
		'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
		'u', 'v', 'w', 'x', 'y', 'z'
        };
	struct archive_string temp_name;
	struct stat st;
	int fd;
	char *tp, *ep;

	fd = -1;
	archive_string_init(&temp_name);
	if (tmpdir == NULL) {
		if (get_tempdir(&temp_name) != ARCHIVE_OK)
			goto exit_tmpfile;
	} else
		archive_strcpy(&temp_name, tmpdir);
	if (temp_name.s[temp_name.length-1] == '/') {
		temp_name.s[temp_name.length-1] = '\0';
		temp_name.length --;
	}
	if (la_stat(temp_name.s, &st) < 0)
		goto exit_tmpfile;
	if (!S_ISDIR(st.st_mode)) {
		errno = ENOTDIR;
		goto exit_tmpfile;
	}
	archive_strcat(&temp_name, "/libarchive_");
	tp = temp_name.s + archive_strlen(&temp_name);
	archive_strcat(&temp_name, "XXXXXXXXXX");
	ep = temp_name.s + archive_strlen(&temp_name);

	do {
		char *p;

		p = tp;
		archive_random(p, ep - p);
		while (p < ep) {
			int d = *((unsigned char *)p) % sizeof(num);
			*p++ = num[d];
		}
		fd = open(temp_name.s, O_CREAT | O_EXCL | O_RDWR | O_CLOEXEC,
			  0600);
	} while (fd < 0 && errno == EEXIST);
	if (fd < 0)
		goto exit_tmpfile;
	__archive_ensure_cloexec_flag(fd);
	unlink(temp_name.s);
exit_tmpfile:
	archive_string_free(&temp_name);
	return (fd);
}
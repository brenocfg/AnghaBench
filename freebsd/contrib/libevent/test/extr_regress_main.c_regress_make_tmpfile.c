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
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 scalar_t__ CreateFileA (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int GetTempFileNameA (char*,char*,int /*<<< orphan*/ ,char*) ; 
 int GetTempPathA (int,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,void const*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _O_RDONLY ; 
 int _open_osfhandle (intptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  umask (int) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int write (int,void const*,size_t) ; 

int
regress_make_tmpfile(const void *data, size_t datalen, char **filename_out)
{
#ifndef _WIN32
	char tmpfilename[32];
	int fd;
	*filename_out = NULL;
	strcpy(tmpfilename, "/tmp/eventtmp.XXXXXX");
#ifdef EVENT__HAVE_UMASK
	umask(0077);
#endif
	fd = mkstemp(tmpfilename);
	if (fd == -1)
		return (-1);
	if (write(fd, data, datalen) != (int)datalen) {
		close(fd);
		return (-1);
	}
	lseek(fd, 0, SEEK_SET);
	/* remove it from the file system */
	unlink(tmpfilename);
	return (fd);
#else
	/* XXXX actually delete the file later */
	char tmpfilepath[MAX_PATH];
	char tmpfilename[MAX_PATH];
	DWORD r, written;
	int tries = 16;
	HANDLE h;
	r = GetTempPathA(MAX_PATH, tmpfilepath);
	if (r > MAX_PATH || r == 0)
		return (-1);
	for (; tries > 0; --tries) {
		r = GetTempFileNameA(tmpfilepath, "LIBEVENT", 0, tmpfilename);
		if (r == 0)
			return (-1);
		h = CreateFileA(tmpfilename, GENERIC_READ|GENERIC_WRITE,
		    0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (h != INVALID_HANDLE_VALUE)
			break;
	}
	if (tries == 0)
		return (-1);
	written = 0;
	*filename_out = strdup(tmpfilename);
	WriteFile(h, data, (DWORD)datalen, &written, NULL);
	/* Closing the fd returned by this function will indeed close h. */
	return _open_osfhandle((intptr_t)h,_O_RDONLY);
#endif
}
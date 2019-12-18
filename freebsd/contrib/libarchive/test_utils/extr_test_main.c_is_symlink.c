#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  buff ;
struct TYPE_7__ {int dwFileAttributes; } ;
struct TYPE_5__ {size_t SubstituteNameLength; size_t SubstituteNameOffset; scalar_t__ PathBuffer; } ;
struct TYPE_6__ {scalar_t__ ReparseTag; TYPE_1__ SymbolicLinkReparseBuffer; } ;
typedef  TYPE_2__ REPARSE_DATA_BUFFER ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  TYPE_3__ BY_HANDLE_FILE_INFORMATION ;
typedef  char BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *) ; 
 int DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ *) ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_REPARSE_POINT ; 
 int FILE_FLAG_BACKUP_SEMANTICS ; 
 int FILE_FLAG_OPEN_REPARSE_POINT ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  FSCTL_GET_REPARSE_POINT ; 
 int GetFileInformationByHandle (scalar_t__,TYPE_3__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ IO_REPARSE_TAG_SYMLINK ; 
 size_t MAXIMUM_REPARSE_DATA_BUFFER_SIZE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int lstat (char const*,struct stat*) ; 
 char* malloc (size_t) ; 
 size_t mbsrtowcs (char*,char const**,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 size_t readlink (char const*,char*,int) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ wcscmp (char*,char*) ; 

__attribute__((used)) static int
is_symlink(const char *file, int line,
    const char *pathname, const char *contents, int isdir)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
	HANDLE h;
	DWORD inbytes;
	REPARSE_DATA_BUFFER *buf;
	BY_HANDLE_FILE_INFORMATION st;
	size_t len, len2;
	wchar_t *linknamew, *contentsw;
	const char *p;
	char *s, *pn;
	int ret = 0;
	BYTE *indata;
	const DWORD flag = FILE_FLAG_BACKUP_SEMANTICS |
	    FILE_FLAG_OPEN_REPARSE_POINT;

	/* Replace slashes with backslashes in pathname */
	pn = malloc((strlen(pathname) + 1) * sizeof(char));
	p = pathname;
	s = pn;
	while(*p != '\0') {
		if(*p == '/')
			*s = '\\';
		else
			*s = *p;
		p++;
		s++;
	}
	*s = '\0';

	h = CreateFileA(pn, 0, FILE_SHARE_READ, NULL, OPEN_EXISTING,
	    flag, NULL);
	free(pn);
	if (h == INVALID_HANDLE_VALUE) {
		failure_start(file, line, "Can't access %s\n", pathname);
		failure_finish(NULL);
		return (0);
	}
	ret = GetFileInformationByHandle(h, &st);
	if (ret == 0) {
		failure_start(file, line,
		    "Can't stat: %s", pathname);
		failure_finish(NULL);
	} else if ((st.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) == 0) {
		failure_start(file, line,
		    "Not a symlink: %s", pathname);
		failure_finish(NULL);
		ret = 0;
	}
	if (isdir && ((st.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)) {
		failure_start(file, line,
		    "Not a directory symlink: %s", pathname);
		failure_finish(NULL);
		ret = 0;
	}
	if (!isdir &&
	    ((st.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)) {
		failure_start(file, line,
		    "Not a file symlink: %s", pathname);
		failure_finish(NULL);
		ret = 0;
	}
	if (ret == 0) {
		CloseHandle(h);
		return (0);
	}

	indata = malloc(MAXIMUM_REPARSE_DATA_BUFFER_SIZE);
	ret = DeviceIoControl(h, FSCTL_GET_REPARSE_POINT, NULL, 0, indata,
	    1024, &inbytes, NULL);
	CloseHandle(h);
	if (ret == 0) {
		free(indata);
		failure_start(file, line,
		    "Could not retrieve symlink target: %s", pathname);
		failure_finish(NULL);
		return (0);
	}

	buf = (REPARSE_DATA_BUFFER *) indata;
	if (buf->ReparseTag != IO_REPARSE_TAG_SYMLINK) {
		free(indata);
		/* File is not a symbolic link */
		failure_start(file, line,
		    "Not a symlink: %s", pathname);
		failure_finish(NULL);
		return (0);
	}

	if (contents == NULL) {
		free(indata);
		return (1);
	}

	len = buf->SymbolicLinkReparseBuffer.SubstituteNameLength;

	linknamew = malloc(len + sizeof(wchar_t));
	if (linknamew == NULL) {
		free(indata);
		return (0);
	}

	memcpy(linknamew, &((BYTE *)buf->SymbolicLinkReparseBuffer.PathBuffer)
	    [buf->SymbolicLinkReparseBuffer.SubstituteNameOffset], len);
	free(indata);

	linknamew[len / sizeof(wchar_t)] = L'\0';

	contentsw = malloc(len + sizeof(wchar_t));
	if (contentsw == NULL) {
		free(linknamew);
		return (0);
	}

	len2 = mbsrtowcs(contentsw, &contents, (len + sizeof(wchar_t)
	    / sizeof(wchar_t)), NULL);

	if (len2 > 0 && wcscmp(linknamew, contentsw) != 0)
		ret = 1;

	free(linknamew);
	free(contentsw);
	return (ret);
#else
	char buff[300];
	struct stat st;
	ssize_t linklen;
	int r;

	(void)isdir; /* UNUSED */
	assertion_count(file, line);
	r = lstat(pathname, &st);
	if (r != 0) {
		failure_start(file, line,
		    "Symlink should exist: %s", pathname);
		failure_finish(NULL);
		return (0);
	}
	if (!S_ISLNK(st.st_mode))
		return (0);
	if (contents == NULL)
		return (1);
	linklen = readlink(pathname, buff, sizeof(buff));
	if (linklen < 0) {
		failure_start(file, line, "Can't read symlink %s", pathname);
		failure_finish(NULL);
		return (0);
	}
	buff[linklen] = '\0';
	if (strcmp(buff, contents) != 0)
		return (0);
	return (1);
#endif
}
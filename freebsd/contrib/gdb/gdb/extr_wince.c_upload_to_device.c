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
typedef  scalar_t__ time_t ;
struct stat {scalar_t__ st_mtime; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  char* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CeCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CeCreateDirectory (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CeCreateFile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CeGetFileTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char const* CeGetLastError () ; 
 int /*<<< orphan*/  CeWriteFile (int /*<<< orphan*/ *,char*,char*,char**,int /*<<< orphan*/ *) ; 
 char* ERROR_ALREADY_EXISTS ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_ALWAYS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UPLOAD_ALWAYS ; 
 scalar_t__ UPLOAD_NEVER ; 
 int /*<<< orphan*/  close (int) ; 
 char* ctime (scalar_t__*) ; 
 int /*<<< orphan*/  error (char*,char const*,...) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int openp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int read (int,char*,int) ; 
 scalar_t__ remote_directory ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 char* strpbrk (char const*,char*) ; 
 scalar_t__ to_time_t (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  towide (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ upload_when ; 
 scalar_t__ xrealloc (char*,int) ; 

char *
upload_to_device (const char *to, const char *from)
{
  HANDLE h;
  const char *dir = remote_directory ?: "\\gdb";
  int len;
  static char *remotefile = NULL;
  LPWSTR wstr;
  char *p;
  DWORD err;
  const char *in_to = to;
  FILETIME crtime, actime, wrtime;
  time_t utime;
  struct stat st;
  int fd;

  /* Look for a path separator and only use trailing part. */
  while ((p = strpbrk (to, "/\\")) != NULL)
    to = p + 1;

  if (!*to)
    error ("no filename found to upload - %s.", in_to);

  len = strlen (dir) + strlen (to) + 2;
  remotefile = (char *) xrealloc (remotefile, len);
  strcpy (remotefile, dir);
  strcat (remotefile, "\\");
  strcat (remotefile, to);

  if (upload_when == UPLOAD_NEVER)
    return remotefile;		/* Don't bother uploading. */

  /* Open the source. */
  if ((fd = openp (getenv ("PATH"), TRUE, (char *) from, O_RDONLY, 0, NULL)) < 0)
    error ("couldn't open %s", from);

  /* Get the time for later comparison. */
  if (fstat (fd, &st))
    st.st_mtime = (time_t) - 1;

  /* Always attempt to create the directory on the remote system. */
  wstr = towide (dir, NULL);
  (void) CeCreateDirectory (wstr, NULL);

  /* Attempt to open the remote file, creating it if it doesn't exist. */
  wstr = towide (remotefile, NULL);
  h = CeCreateFile (wstr, GENERIC_READ | GENERIC_WRITE, 0, NULL,
		    OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

  /* Some kind of problem? */
  err = CeGetLastError ();
  if (h == NULL || h == INVALID_HANDLE_VALUE)
    error ("error opening file \"%s\".  Windows error %d.",
	   remotefile, err);

  CeGetFileTime (h, &crtime, &actime, &wrtime);
  utime = to_time_t (&wrtime);
#if 0
  if (utime < st.st_mtime)
    {
      char buf[80];
      strcpy (buf, ctime(&utime));
      printf ("%s < %s\n", buf, ctime(&st.st_mtime));
    }
#endif
  /* See if we need to upload the file. */
  if (upload_when == UPLOAD_ALWAYS ||
      err != ERROR_ALREADY_EXISTS ||
      !CeGetFileTime (h, &crtime, &actime, &wrtime) ||
      to_time_t (&wrtime) < st.st_mtime)
    {
      DWORD nbytes;
      char buf[4096];
      int n;

      /* Upload the file. */
      while ((n = read (fd, buf, sizeof (buf))) > 0)
	if (!CeWriteFile (h, buf, (DWORD) n, &nbytes, NULL))
	  error ("error writing to remote device - %d.",
		 CeGetLastError ());
    }

  close (fd);
  if (!CeCloseHandle (h))
    error ("error closing remote file - %d.", CeGetLastError ());

  return remotefile;
}
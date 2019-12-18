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
typedef  int /*<<< orphan*/  cmdbuf ;

/* Variables and functions */
 int COMPLETE ; 
 int /*<<< orphan*/  DPRINTF (char*,char const*,...) ; 
 int /*<<< orphan*/  FREEPTR (char*) ; 
 int MAX_C_NAME ; 
 int /*<<< orphan*/  STRorNULL (char*) ; 
 int auto_fetch (int,char**) ; 
 int code ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ftp_malloc (size_t) ; 
 char* ftp_strdup (char const*) ; 
 int /*<<< orphan*/  mput (int,char**) ; 
 int /*<<< orphan*/  put (int,char**) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
auto_put(int argc, char **argv, const char *uploadserver)
{
	char	*uargv[4], *path, *pathsep;
	int	 uargc, rval, argpos;
	size_t	 len;
	char	 cmdbuf[MAX_C_NAME];

	(void)strlcpy(cmdbuf, "mput", sizeof(cmdbuf));
	uargv[0] = cmdbuf;
	uargv[1] = argv[0];
	uargc = 2;
	uargv[2] = uargv[3] = NULL;
	pathsep = NULL;
	rval = 1;

	DPRINTF("auto_put: target `%s'\n", uploadserver);

	path = ftp_strdup(uploadserver);
	len = strlen(path);
	if (path[len - 1] != '/' && path[len - 1] != ':') {
			/*
			 * make sure we always pass a directory to auto_fetch
			 */
		if (argc > 1) {		/* more than one file to upload */
			len = strlen(uploadserver) + 2;	/* path + "/" + "\0" */
			free(path);
			path = (char *)ftp_malloc(len);
			(void)strlcpy(path, uploadserver, len);
			(void)strlcat(path, "/", len);
		} else {		/* single file to upload */
			(void)strlcpy(cmdbuf, "put", sizeof(cmdbuf));
			uargv[0] = cmdbuf;
			pathsep = strrchr(path, '/');
			if (pathsep == NULL) {
				pathsep = strrchr(path, ':');
				if (pathsep == NULL) {
					warnx("Invalid URL `%s'", path);
					goto cleanup_auto_put;
				}
				pathsep++;
				uargv[2] = ftp_strdup(pathsep);
				pathsep[0] = '/';
			} else
				uargv[2] = ftp_strdup(pathsep + 1);
			pathsep[1] = '\0';
			uargc++;
		}
	}
	DPRINTF("auto_put: URL `%s' argv[2] `%s'\n",
	    path, STRorNULL(uargv[2]));

			/* connect and cwd */
	rval = auto_fetch(1, &path);
	if(rval >= 0)
		goto cleanup_auto_put;

	rval = 0;

			/* target filename provided; upload 1 file */
			/* XXX : is this the best way? */
	if (uargc == 3) {
		uargv[1] = argv[0];
		put(uargc, uargv);
		if ((code / 100) != COMPLETE)
			rval = 1;
	} else {	/* otherwise a target dir: upload all files to it */
		for(argpos = 0; argv[argpos] != NULL; argpos++) {
			uargv[1] = argv[argpos];
			mput(uargc, uargv);
			if ((code / 100) != COMPLETE) {
				rval = argpos + 1;
				break;
			}
		}
	}

 cleanup_auto_put:
	free(path);
	FREEPTR(uargv[2]);
	return (rval);
}
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
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_INVALIDFILE ; 
 int /*<<< orphan*/  ISC_R_NOMEMORY ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 char* isc_mem_allocate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isc_mem_free (int /*<<< orphan*/ *,char*) ; 
 char* isc_mem_strdup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 char* strrchr (char*,char) ; 

isc_result_t
isc_file_splitpath(isc_mem_t *mctx, char *path, char **dirnam, char **basenam)
{
	char *dir, *file, *slash;

	REQUIRE(path != NULL);

	slash = strrchr(path, '/');

	if (slash == path) {
		file = ++slash;
		dir = isc_mem_strdup(mctx, "/");
	} else if (slash != NULL) {
		file = ++slash;
		dir = isc_mem_allocate(mctx, slash - path);
		if (dir != NULL)
			strlcpy(dir, path, slash - path);
	} else {
		file = path;
		dir = isc_mem_strdup(mctx, ".");
	}

	if (dir == NULL)
		return (ISC_R_NOMEMORY);

	if (*file == '\0') {
		isc_mem_free(mctx, dir);
		return (ISC_R_INVALIDFILE);
	}

	*dirnam = dir;
	*basenam = file;

	return (ISC_R_SUCCESS);
}
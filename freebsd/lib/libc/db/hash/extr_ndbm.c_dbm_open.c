#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_3__ {int bsize; int ffactor; int nelem; scalar_t__ lorder; int /*<<< orphan*/ * hash; scalar_t__ cachesize; } ;
typedef  TYPE_1__ HASHINFO ;
typedef  int /*<<< orphan*/  DBM ;

/* Variables and functions */
 char const* DBM_SUFFIX ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int MAXPATHLEN ; 
 scalar_t__ __hash_open (char*,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

extern DBM *
dbm_open(const char *file, int flags, mode_t mode)
{
	HASHINFO info;
	char path[MAXPATHLEN];

	info.bsize = 4096;
	info.ffactor = 40;
	info.nelem = 1;
	info.cachesize = 0;
	info.hash = NULL;
	info.lorder = 0;

	if( strlen(file) >= sizeof(path) - strlen(DBM_SUFFIX)) {
		errno = ENAMETOOLONG;
		return(NULL);
	}
	(void)strcpy(path, file);
	(void)strcat(path, DBM_SUFFIX);
	return ((DBM *)__hash_open(path, flags, mode, &info, 0));
}
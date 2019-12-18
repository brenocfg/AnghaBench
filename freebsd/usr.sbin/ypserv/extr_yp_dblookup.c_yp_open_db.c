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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  DB ;

/* Variables and functions */
 int /*<<< orphan*/  DB_HASH ; 
#define  EFTYPE 130 
#define  ENFILE 129 
#define  ENOENT 128 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PERM_SECURE ; 
 int /*<<< orphan*/  YP_BADARGS ; 
 int /*<<< orphan*/  YP_BADDB ; 
 int /*<<< orphan*/  YP_NODOM ; 
 int /*<<< orphan*/  YP_NOMAP ; 
 int /*<<< orphan*/  YP_TRUE ; 
 int /*<<< orphan*/  YP_YPERR ; 
 int /*<<< orphan*/ * dbopen (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*,char const*) ; 
 scalar_t__ strchr (char const*,char) ; 
 char* yp_dir ; 
 int /*<<< orphan*/  yp_errno ; 
 int /*<<< orphan*/  yp_error (char*) ; 
 int /*<<< orphan*/  yp_flush () ; 
 scalar_t__ yp_validdomain (char const*) ; 

DB *
yp_open_db(const char *domain, const char *map)
{
	DB *dbp = NULL;
	char buf[MAXPATHLEN + 2];

	yp_errno = YP_TRUE;

	if (map[0] == '.' || strchr(map, '/')) {
		yp_errno = YP_BADARGS;
		return (NULL);
	}

#ifdef DB_CACHE
	if (yp_validdomain(domain)) {
		yp_errno = YP_NODOM;
		return(NULL);
	}
#endif
	snprintf(buf, sizeof(buf), "%s/%s/%s", yp_dir, domain, map);

#ifdef DB_CACHE
again:
#endif
	dbp = dbopen(buf, O_RDONLY, PERM_SECURE, DB_HASH, NULL);

	if (dbp == NULL) {
		switch (errno) {
#ifdef DB_CACHE
		case ENFILE:
			/*
			 * We ran out of file descriptors. Nuke an
			 * open one and try again.
			 */
			yp_error("ran out of file descriptors");
			yp_flush();
			goto again;
			break;
#endif
		case ENOENT:
			yp_errno = YP_NOMAP;
			break;
		case EFTYPE:
			yp_errno = YP_BADDB;
			break;
		default:
			yp_errno = YP_YPERR;
			break;
		}
	}

	return (dbp);
}
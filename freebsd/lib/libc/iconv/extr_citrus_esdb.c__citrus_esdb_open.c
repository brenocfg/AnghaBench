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
struct _region {int dummy; } ;
struct _citrus_esdb {int dummy; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;

/* Variables and functions */
 int ENOENT ; 
 char* ESDB_ALIAS ; 
 char* ESDB_DIR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  _LOOKUP_CASE_IGNORE ; 
 char* _PATH_ESDB ; 
 char* _lookup_alias (char*,char const*,char*,int,int /*<<< orphan*/ ) ; 
 char* _lookup_simple (char*,char const*,char*,int,int /*<<< orphan*/ ) ; 
 int _map_file (struct _region*,char*) ; 
 int /*<<< orphan*/  _unmap_file (struct _region*) ; 
 int conv_esdb (struct _citrus_esdb*,struct _region*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 

int
_citrus_esdb_open(struct _citrus_esdb *db, const char *esname)
{
	struct _region fr;
	const char *realname, *encfile;
	char buf1[PATH_MAX], buf2[PATH_MAX], path[PATH_MAX];
	int ret;

	snprintf(path, sizeof(path), "%s/%s", _PATH_ESDB, ESDB_ALIAS);
	realname = _lookup_alias(path, esname, buf1, sizeof(buf1),
	    _LOOKUP_CASE_IGNORE);

	snprintf(path, sizeof(path), "%s/%s", _PATH_ESDB, ESDB_DIR);
	encfile = _lookup_simple(path, realname, buf2, sizeof(buf2),
	    _LOOKUP_CASE_IGNORE);
	if (encfile == NULL)
		return (ENOENT);

	/* open file */
	snprintf(path, sizeof(path), "%s/%s", _PATH_ESDB, encfile);
	ret = _map_file(&fr, path);
	if (ret)
		return (ret);

	ret = conv_esdb(db, &fr);

	_unmap_file(&fr);

	return (ret);
}
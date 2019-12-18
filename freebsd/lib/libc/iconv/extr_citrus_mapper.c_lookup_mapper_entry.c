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
struct _memstream {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int PATH_MAX ; 
 char* _CITRUS_MAPPER_DIR ; 
 char* _bcs_skip_nonws_len (char const*,size_t*) ; 
 char* _bcs_skip_ws_len (char const*,size_t*) ; 
 int _map_file (struct _region*,char*) ; 
 int /*<<< orphan*/  _memstream_bind (struct _memstream*,struct _region*) ; 
 char* _memstream_matchline (struct _memstream*,char const*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _unmap_file (struct _region*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static int
lookup_mapper_entry(const char *dir, const char *mapname, void *linebuf,
    size_t linebufsize, const char **module, const char **variable)
{
	struct _region r;
	struct _memstream ms;
	const char *cp, *cq;
	char *p;
	char path[PATH_MAX];
	size_t len;
	int ret;

	/* create mapper.dir path */
	snprintf(path, (size_t)PATH_MAX, "%s/%s", dir, _CITRUS_MAPPER_DIR);

	/* open read stream */
	ret = _map_file(&r, path);
	if (ret)
		return (ret);

	_memstream_bind(&ms, &r);

	/* search the line matching to the map name */
	cp = _memstream_matchline(&ms, mapname, &len, 0);
	if (!cp) {
		ret = ENOENT;
		goto quit;
	}
	if (!len || len > linebufsize - 1) {
		ret = EINVAL;
		goto quit;
	}

	p = linebuf;
	/* get module name */
	*module = p;
	cq = _bcs_skip_nonws_len(cp, &len);
	strlcpy(p, cp, (size_t)(cq - cp + 1));
	p += cq - cp + 1;

	/* get variable */
	*variable = p;
	cp = _bcs_skip_ws_len(cq, &len);
	strlcpy(p, cp, len + 1);

	ret = 0;

quit:
	_unmap_file(&r);
	return (ret);
}
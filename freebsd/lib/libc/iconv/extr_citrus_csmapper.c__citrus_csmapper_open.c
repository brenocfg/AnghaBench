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
typedef  int uint32_t ;
struct _citrus_csmapper {int dummy; } ;
typedef  int /*<<< orphan*/  pivot ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ALIAS ; 
 int ENOENT ; 
 int PATH_MAX ; 
 int _CSMAPPER_F_PREVENT_PIVOT ; 
 int /*<<< orphan*/  _LOOKUP_CASE_IGNORE ; 
 int /*<<< orphan*/  _PATH_CSMAPPER ; 
 int _citrus_mapper_create_area (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* _lookup_alias (int /*<<< orphan*/ ,char const*,char*,int,int /*<<< orphan*/ ) ; 
 int _mapper_open (int /*<<< orphan*/ ,struct _citrus_csmapper**,char*) ; 
 int find_best_pivot (char const*,char const*,char*,int,unsigned long*) ; 
 int get_none (int /*<<< orphan*/ ,struct _citrus_csmapper**) ; 
 int /*<<< orphan*/  maparea ; 
 int open_serial_mapper (int /*<<< orphan*/ ,struct _citrus_csmapper**,char const*,char*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

int
_citrus_csmapper_open(struct _citrus_csmapper * __restrict * __restrict rcsm,
    const char * __restrict src, const char * __restrict dst, uint32_t flags,
    unsigned long *rnorm)
{
	const char *realsrc, *realdst;
	char buf1[PATH_MAX], buf2[PATH_MAX], key[PATH_MAX], pivot[PATH_MAX];
	unsigned long norm;
	int ret;

	norm = 0;

	ret = _citrus_mapper_create_area(&maparea, _PATH_CSMAPPER);
	if (ret)
		return (ret);

	realsrc = _lookup_alias(CS_ALIAS, src, buf1, sizeof(buf1),
	    _LOOKUP_CASE_IGNORE);
	realdst = _lookup_alias(CS_ALIAS, dst, buf2, sizeof(buf2),
	    _LOOKUP_CASE_IGNORE);
	if (!strcmp(realsrc, realdst)) {
		ret = get_none(maparea, rcsm);
		if (ret == 0 && rnorm != NULL)
			*rnorm = 0;
		return (ret);
	}

	snprintf(key, sizeof(key), "%s/%s", realsrc, realdst);

	ret = _mapper_open(maparea, rcsm, key);
	if (ret == 0) {
		if (rnorm != NULL)
			*rnorm = 0;
		return (0);
	}
	if (ret != ENOENT || (flags & _CSMAPPER_F_PREVENT_PIVOT)!=0)
		return (ret);

	ret = find_best_pivot(realsrc, realdst, pivot, sizeof(pivot), &norm);
	if (ret)
		return (ret);

	ret = open_serial_mapper(maparea, rcsm, realsrc, pivot, realdst);
	if (ret == 0 && rnorm != NULL)
		*rnorm = norm;

	return (ret);
}
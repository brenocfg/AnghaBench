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
struct _citrus_mapper_area {int /*<<< orphan*/  ma_cache; int /*<<< orphan*/  ma_dir; } ;
struct _citrus_mapper {int cm_refcount; int /*<<< orphan*/ * cm_key; } ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _CITRUS_HASH_INSERT (int /*<<< orphan*/ *,struct _citrus_mapper*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _CITRUS_HASH_SEARCH (int /*<<< orphan*/ *,struct _citrus_mapper*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  _mapper_close (struct _citrus_mapper*) ; 
 int /*<<< orphan*/  cm_entry ; 
 int /*<<< orphan*/  cm_lock ; 
 int errno ; 
 int hash_func (char const*) ; 
 int lookup_mapper_entry (int /*<<< orphan*/ ,char const*,char*,size_t,char const**,char const**) ; 
 int mapper_open (struct _citrus_mapper_area*,struct _citrus_mapper**,char const*,char const*) ; 
 int /*<<< orphan*/  match_func ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

int
_citrus_mapper_open(struct _citrus_mapper_area *__restrict ma,
    struct _citrus_mapper * __restrict * __restrict rcm,
    const char * __restrict mapname)
{
	struct _citrus_mapper *cm;
	char linebuf[PATH_MAX];
	const char *module, *variable;
	int hashval, ret;

	variable = NULL;

	WLOCK(&cm_lock);

	/* search in the cache */
	hashval = hash_func(mapname);
	_CITRUS_HASH_SEARCH(&ma->ma_cache, cm, cm_entry, match_func, mapname,
	    hashval);
	if (cm) {
		/* found */
		cm->cm_refcount++;
		*rcm = cm;
		ret = 0;
		goto quit;
	}

	/* search mapper entry */
	ret = lookup_mapper_entry(ma->ma_dir, mapname, linebuf,
	    (size_t)PATH_MAX, &module, &variable);
	if (ret)
		goto quit;

	/* open mapper */
	UNLOCK(&cm_lock);
	ret = mapper_open(ma, &cm, module, variable);
	WLOCK(&cm_lock);
	if (ret)
		goto quit;
	cm->cm_key = strdup(mapname);
	if (cm->cm_key == NULL) {
		ret = errno;
		_mapper_close(cm);
		goto quit;	
	}

	/* insert to the cache */
	cm->cm_refcount = 1;
	_CITRUS_HASH_INSERT(&ma->ma_cache, cm, cm_entry, hashval);

	*rcm = cm;
	ret = 0;
quit:
	UNLOCK(&cm_lock);

	return (ret);
}
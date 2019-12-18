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
struct stat {int dummy; } ;
struct _citrus_mapper_area {int /*<<< orphan*/  ma_cache; int /*<<< orphan*/ * ma_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_HASH_SIZE ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _CITRUS_HASH_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* _CITRUS_MAPPER_DIR ; 
 int /*<<< orphan*/  cm_lock ; 
 int errno ; 
 int /*<<< orphan*/  free (struct _citrus_mapper_area*) ; 
 struct _citrus_mapper_area* malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char*) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

int
_citrus_mapper_create_area(
    struct _citrus_mapper_area *__restrict *__restrict rma,
    const char *__restrict area)
{
	struct _citrus_mapper_area *ma;
	struct stat st;
	char path[PATH_MAX];
	int ret;

	WLOCK(&cm_lock);

	if (*rma != NULL) {
		ret = 0;
		goto quit;
	}

	snprintf(path, (size_t)PATH_MAX, "%s/%s", area, _CITRUS_MAPPER_DIR);

	ret = stat(path, &st);
	if (ret)
		goto quit;

	ma = malloc(sizeof(*ma));
	if (ma == NULL) {
		ret = errno;
		goto quit;
	}
	ma->ma_dir = strdup(area);
	if (ma->ma_dir == NULL) {
		ret = errno;
		free(ma);
		goto quit;
	}
	_CITRUS_HASH_INIT(&ma->ma_cache, CM_HASH_SIZE);

	*rma = ma;
	ret = 0;
quit:
	UNLOCK(&cm_lock);

	return (ret);
}
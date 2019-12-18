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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_3__ {scalar_t__ fa_magic; int /*<<< orphan*/ * fa_cache; } ;
typedef  TYPE_1__ fileargs_t ;

/* Variables and functions */
 scalar_t__ FILEARGS_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * dnvlist_get_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct stat*,void const*,size_t) ; 
 int /*<<< orphan*/  nvlist_exists_binary (int /*<<< orphan*/  const*,char*) ; 
 void* nvlist_get_binary (int /*<<< orphan*/  const*,char*,size_t*) ; 

__attribute__((used)) static int
fileargs_get_lstat_cache(fileargs_t *fa, const char *name, struct stat *sb)
{
	const nvlist_t *nvl;
	size_t size;
	const void *buf;

	assert(fa != NULL);
	assert(fa->fa_magic == FILEARGS_MAGIC);
	assert(name != NULL);

	if (fa->fa_cache == NULL)
		return (-1);

	nvl = dnvlist_get_nvlist(fa->fa_cache, name, NULL);
	if (nvl == NULL)
		return (-1);

	if (!nvlist_exists_binary(nvl, "stat")) {
		return (-1);
	}

	buf = nvlist_get_binary(nvl, "stat", &size);
	assert(size == sizeof(*sb));
	memcpy(sb, buf, size);

	return (0);
}
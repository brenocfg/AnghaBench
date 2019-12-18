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
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_3__ {int /*<<< orphan*/  fa_chann; } ;
typedef  TYPE_1__ fileargs_t ;

/* Variables and functions */
 int /*<<< orphan*/  NV_FLAG_NO_UNIQUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cap_xfer_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static nvlist_t*
fileargs_fetch(fileargs_t *fa, const char *name, const char *cmd)
{
	nvlist_t *nvl;
	int serrno;

	assert(fa != NULL);
	assert(name != NULL);

	nvl = nvlist_create(NV_FLAG_NO_UNIQUE);
	nvlist_add_string(nvl, "cmd", cmd);
	nvlist_add_string(nvl, "name", name);

	nvl = cap_xfer_nvlist(fa->fa_chann, nvl);
	if (nvl == NULL)
		return (NULL);

	if (nvlist_get_number(nvl, "error") != 0) {
		serrno = (int)nvlist_get_number(nvl, "error");
		nvlist_destroy(nvl);
		errno = serrno;
		return (NULL);
	}

	return (nvl);
}
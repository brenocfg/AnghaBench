#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_10__ {scalar_t__ nvl_error; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ ERRNO_OR_DEFAULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRNO_SET (scalar_t__) ; 
 int /*<<< orphan*/  nv_free (TYPE_1__**) ; 
 int /*<<< orphan*/  nvlist_destroy (TYPE_1__*) ; 
 scalar_t__ nvlist_error (TYPE_1__*) ; 
 int /*<<< orphan*/ * nvlist_get_pararr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_move_nvpair (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvpair_move_nvlist_array (char const*,TYPE_1__**,size_t) ; 

void
nvlist_move_nvlist_array(nvlist_t *nvl, const char *name, nvlist_t **value,
    size_t nitems)
{
	nvpair_t *nvp;
	size_t i;

	if (nvlist_error(nvl) != 0) {
		if (value != NULL) {
			for (i = 0; i < nitems; i++) {
				if (nvlist_get_pararr(value[i], NULL) == NULL)
					nvlist_destroy(value[i]);
			}
		}
		nv_free(value);
		ERRNO_SET(nvlist_error(nvl));
		return;
	}

	nvp = nvpair_move_nvlist_array(name, value, nitems);
	if (nvp == NULL) {
		nvl->nvl_error = ERRNO_OR_DEFAULT(ENOMEM);
		ERRNO_SET(nvl->nvl_error);
	} else {
		(void)nvlist_move_nvpair(nvl, nvp);
	}
}
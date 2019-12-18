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
struct _citrus_mapper_area {int dummy; } ;
struct _citrus_csmapper {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WLOCK (int /*<<< orphan*/ *) ; 
 int _mapper_open_direct (struct _citrus_mapper_area*,struct _citrus_csmapper**,char*,char*) ; 
 int /*<<< orphan*/  _mapper_set_persistent (struct _citrus_csmapper*) ; 
 struct _citrus_csmapper* csm_none ; 
 int /*<<< orphan*/  ma_lock ; 

__attribute__((used)) static int
get_none(struct _citrus_mapper_area *__restrict ma,
    struct _citrus_csmapper *__restrict *__restrict rcsm)
{
	int ret;

	WLOCK(&ma_lock);
	if (csm_none) {
		*rcsm = csm_none;
		ret = 0;
		goto quit;
	}

	ret = _mapper_open_direct(ma, &csm_none, "mapper_none", "");
	if (ret)
		goto quit;
	_mapper_set_persistent(csm_none);

	*rcsm = csm_none;
	ret = 0;
quit:
	UNLOCK(&ma_lock);
	return (ret);
}
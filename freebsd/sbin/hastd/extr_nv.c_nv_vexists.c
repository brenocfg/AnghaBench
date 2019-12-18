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
typedef  int /*<<< orphan*/  va_list ;
struct nvhdr {int dummy; } ;
struct nv {int nv_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_TYPE_NONE ; 
 int errno ; 
 struct nvhdr* nv_find (struct nv*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nv_vexists(struct nv *nv, const char *namefmt, va_list nameap)
{
	struct nvhdr *nvh;
	int snverror, serrno;

	if (nv == NULL)
		return (false);

	serrno = errno;
	snverror = nv->nv_error;

	nvh = nv_find(nv, NV_TYPE_NONE, namefmt, nameap);

	errno = serrno;
	nv->nv_error = snverror;

	return (nvh != NULL);
}
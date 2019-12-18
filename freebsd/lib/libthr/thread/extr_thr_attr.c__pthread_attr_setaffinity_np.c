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
typedef  TYPE_1__* pthread_attr_t ;
typedef  int /*<<< orphan*/  cpuset_t ;
struct TYPE_3__ {size_t cpusetsize; int /*<<< orphan*/ * cpuset; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 size_t _get_kern_cpuset_size () ; 
 int /*<<< orphan*/ * calloc (int,size_t) ; 
 int errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

int
_pthread_attr_setaffinity_np(pthread_attr_t *pattr, size_t cpusetsize,
	const cpuset_t *cpusetp)
{
	pthread_attr_t attr;
	int ret;

	if (pattr == NULL || (attr = (*pattr)) == NULL)
		ret = EINVAL;
	else {
		if (cpusetsize == 0 || cpusetp == NULL) {
			if (attr->cpuset != NULL) {
				free(attr->cpuset);
				attr->cpuset = NULL;
				attr->cpusetsize = 0;
			}
			return (0);
		}
		size_t kern_size = _get_kern_cpuset_size();
		/* Kernel rejects small set, we check it here too. */ 
		if (cpusetsize < kern_size)
			return (ERANGE);
		if (cpusetsize > kern_size) {
			/* Kernel checks invalid bits, we check it here too. */
			size_t i;
			for (i = kern_size; i < cpusetsize; ++i) {
				if (((const char *)cpusetp)[i])
					return (EINVAL);
			}
		}
		if (attr->cpuset == NULL) {
			attr->cpuset = calloc(1, kern_size);
			if (attr->cpuset == NULL)
				return (errno);
			attr->cpusetsize = kern_size;
		}
		memcpy(attr->cpuset, cpusetp, kern_size);
		ret = 0;
	}
	return (ret);
}
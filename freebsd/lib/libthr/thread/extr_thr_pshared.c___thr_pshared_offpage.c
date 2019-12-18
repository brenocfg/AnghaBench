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
struct pthread {int dummy; } ;

/* Variables and functions */
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  UMTX_OP_SHM ; 
 int /*<<< orphan*/  UMTX_SHM_CREAT ; 
 int /*<<< orphan*/  UMTX_SHM_LOOKUP ; 
 struct pthread* _get_curthread () ; 
 int _umtx_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 void* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pshared_clean (void*,void*) ; 
 int pshared_insert (void*,void**) ; 
 void* pshared_lookup (void*) ; 
 int /*<<< orphan*/  pshared_rlock (struct pthread*) ; 
 int /*<<< orphan*/  pshared_unlock (struct pthread*) ; 
 int /*<<< orphan*/  pshared_wlock (struct pthread*) ; 

void *
__thr_pshared_offpage(void *key, int doalloc)
{
	struct pthread *curthread;
	void *res;
	int fd, ins_done;

	curthread = _get_curthread();
	pshared_rlock(curthread);
	res = pshared_lookup(key);
	pshared_unlock(curthread);
	if (res != NULL)
		return (res);
	fd = _umtx_op(NULL, UMTX_OP_SHM, doalloc ? UMTX_SHM_CREAT :
	    UMTX_SHM_LOOKUP, key, NULL);
	if (fd == -1)
		return (NULL);
	res = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);
	if (res == MAP_FAILED)
		return (NULL);
	pshared_wlock(curthread);
	ins_done = pshared_insert(key, &res);
	pshared_unlock(curthread);
	if (!ins_done) {
		pshared_clean(key, res);
		res = NULL;
	}
	return (res);
}
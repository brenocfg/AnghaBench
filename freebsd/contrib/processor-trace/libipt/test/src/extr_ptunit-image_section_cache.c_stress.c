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
struct ptunit_result {int dummy; } ;
typedef  void iscache_fixture ;

/* Variables and functions */
 int num_threads ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int (*) (void*),void*) ; 
 int /*<<< orphan*/  ptunit_thrd_create ; 

__attribute__((used)) static struct ptunit_result stress(struct iscache_fixture *cfix,
				   int (*worker)(void *))
{
	int errcode;

#if defined(FEATURE_THREADS)
	{
		int thrd;

		for (thrd = 0; thrd < num_threads; ++thrd)
			ptu_test(ptunit_thrd_create, &cfix->thrd, worker, cfix);
	}
#endif /* defined(FEATURE_THREADS) */

	errcode = worker(cfix);
	ptu_int_eq(errcode, 0);

	return ptu_passed();
}
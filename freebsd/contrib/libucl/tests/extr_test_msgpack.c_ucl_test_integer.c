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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  ucl_object_t ;
typedef  int /*<<< orphan*/  curf ;

/* Variables and functions */
 int INT16_MAX ; 
 int INT32_MAX ; 
 int /*<<< orphan*/  UCL_ARRAY ; 
 int UINT16_MAX ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  memcpy (double*,int*,int) ; 
 int nelt ; 
 int pcg32_random () ; 
 int /*<<< orphan*/  ucl_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_object_fromdouble (double) ; 
 int /*<<< orphan*/  ucl_object_fromint (int) ; 
 int /*<<< orphan*/ * ucl_object_typed_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ucl_object_t*
ucl_test_integer (void)
{
	ucl_object_t *res;
	int count, i;
	uint64_t cur;
	double curf;

	res = ucl_object_typed_new (UCL_ARRAY);
	count = pcg32_random () % nelt;

	for (i = 0; i < count; i ++) {
		cur = ((uint64_t)pcg32_random ()) << 32 | pcg32_random ();
		ucl_array_append (res, ucl_object_fromint (cur % 128));
		ucl_array_append (res, ucl_object_fromint (-(cur % 128)));
		cur = ((uint64_t)pcg32_random ()) << 32 | pcg32_random ();
		ucl_array_append (res, ucl_object_fromint (cur % UINT16_MAX));
		ucl_array_append (res, ucl_object_fromint (-(cur % INT16_MAX)));
		cur = ((uint64_t)pcg32_random ()) << 32 | pcg32_random ();
		ucl_array_append (res, ucl_object_fromint (cur % UINT32_MAX));
		ucl_array_append (res, ucl_object_fromint (-(cur % INT32_MAX)));
		cur = ((uint64_t)pcg32_random ()) << 32 | pcg32_random ();
		ucl_array_append (res, ucl_object_fromint (cur));
		ucl_array_append (res, ucl_object_fromint (-cur));
		/* Double version */
		cur = ((uint64_t)pcg32_random ()) << 32 | pcg32_random ();
		curf = (cur % 128) / 19 * 16;
		ucl_array_append (res, ucl_object_fromdouble (curf));
		cur = ((uint64_t)pcg32_random ()) << 32 | pcg32_random ();
		curf = -(cur % 128) / 19 * 16;
		ucl_array_append (res, ucl_object_fromdouble (curf));
		cur = ((uint64_t)pcg32_random ()) << 32 | pcg32_random ();
		curf = (cur % 65536) / 19 * 16;
		ucl_array_append (res, ucl_object_fromdouble (curf));
		ucl_array_append (res, ucl_object_fromdouble (-curf));
		cur = ((uint64_t)pcg32_random ()) << 32 | pcg32_random ();
		curf = (cur % INT32_MAX) / 19 * 16;
		ucl_array_append (res, ucl_object_fromdouble (curf));
		cur = ((uint64_t)pcg32_random ()) << 32 | pcg32_random ();
		memcpy (&curf, &cur, sizeof (curf));
		ucl_array_append (res, ucl_object_fromint (cur));
	}

	return res;
}
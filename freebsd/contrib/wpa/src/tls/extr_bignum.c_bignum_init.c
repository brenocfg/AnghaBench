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
struct bignum {int dummy; } ;
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 scalar_t__ MP_OKAY ; 
 scalar_t__ mp_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct bignum*) ; 
 struct bignum* os_zalloc (int) ; 

struct bignum * bignum_init(void)
{
	struct bignum *n = os_zalloc(sizeof(mp_int));
	if (n == NULL)
		return NULL;
	if (mp_init((mp_int *) n) != MP_OKAY) {
		os_free(n);
		n = NULL;
	}
	return n;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct ino_bucket {unsigned int __irq; } ;

/* Variables and functions */
 scalar_t__ __va (unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long) ; 
 unsigned long sun4v_vintr_get_cookie (int /*<<< orphan*/ ,unsigned int,unsigned long*) ; 

__attribute__((used)) static unsigned int cookie_exists(u32 devhandle, unsigned int devino)
{
	unsigned long hv_err, cookie;
	struct ino_bucket *bucket;
	unsigned int irq = 0U;

	hv_err = sun4v_vintr_get_cookie(devhandle, devino, &cookie);
	if (hv_err) {
		pr_err("HV get cookie failed hv_err = %ld\n", hv_err);
		goto out;
	}

	if (cookie & ((1UL << 63UL))) {
		cookie = ~cookie;
		bucket = (struct ino_bucket *) __va(cookie);
		irq = bucket->__irq;
	}
out:
	return irq;
}
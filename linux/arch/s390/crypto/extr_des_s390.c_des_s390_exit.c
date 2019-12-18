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

/* Variables and functions */
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ ) ; 
 scalar_t__ ctrblk ; 
 size_t des_s390_algs_num ; 
 int /*<<< orphan*/ * des_s390_algs_ptr ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static void des_s390_exit(void)
{
	while (des_s390_algs_num--)
		crypto_unregister_alg(des_s390_algs_ptr[des_s390_algs_num]);
	if (ctrblk)
		free_page((unsigned long) ctrblk);
}
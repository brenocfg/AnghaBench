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
struct cryptocap {int* cc_kalg; } ;
struct cryptkop {size_t krp_op; } ;

/* Variables and functions */
 int CRYPTO_ALG_FLAG_SUPPORTED ; 

__attribute__((used)) static __inline int
kdriver_suitable(const struct cryptocap *cap, const struct cryptkop *krp)
{
	return (cap->cc_kalg[krp->krp_op] & CRYPTO_ALG_FLAG_SUPPORTED) != 0;
}
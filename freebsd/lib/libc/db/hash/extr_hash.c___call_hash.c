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
typedef  unsigned int u_int32_t ;
struct TYPE_3__ {unsigned int (* hash ) (char*,int) ;unsigned int HIGH_MASK; unsigned int MAX_BUCKET; unsigned int LOW_MASK; } ;
typedef  TYPE_1__ HTAB ;

/* Variables and functions */
 unsigned int stub1 (char*,int) ; 

u_int32_t
__call_hash(HTAB *hashp, char *k, int len)
{
	unsigned int n, bucket;

	n = hashp->hash(k, len);
	bucket = n & hashp->HIGH_MASK;
	if (bucket > hashp->MAX_BUCKET)
		bucket = bucket & hashp->LOW_MASK;
	return (bucket);
}
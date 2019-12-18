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
struct scatterlist {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *alloc_req_buf(int nents, int extralen, gfp_t gfp)
{
	size_t size;

	size = sizeof(struct scatterlist) * nents;
	size += extralen;

	return kzalloc(size, gfp);
}
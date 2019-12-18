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
typedef  int uint8_t ;
typedef  int qidx_t ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static inline qidx_t
get_inuse(int size, qidx_t cidx, qidx_t pidx, uint8_t gen)
{
	qidx_t used;

	if (pidx > cidx)
		used = pidx - cidx;
	else if (pidx < cidx)
		used = size - cidx + pidx;
	else if (gen == 0 && pidx == cidx)
		used = 0;
	else if (gen == 1 && pidx == cidx)
		used = size;
	else
		panic("bad state");

	return (used);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {uintptr_t nvb_cur; uintptr_t nvb_lim; } ;
typedef  TYPE_1__ nvbuf_t ;
struct TYPE_5__ {TYPE_1__* nva_arg; } ;
typedef  TYPE_2__ nv_alloc_t ;

/* Variables and functions */
 uintptr_t P2ROUNDUP (uintptr_t,int) ; 

__attribute__((used)) static void *
nv_fixed_alloc(nv_alloc_t *nva, size_t size)
{
	nvbuf_t *nvb = nva->nva_arg;
	uintptr_t new = nvb->nvb_cur;

	if (size == 0 || new + size > nvb->nvb_lim)
		return (NULL);

	nvb->nvb_cur = P2ROUNDUP(new + size, sizeof (uintptr_t));

	return ((void *)new);
}
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
 void* lwork (void const*,void const*,size_t*,size_t,int (*) (void const*,void const*),int /*<<< orphan*/ ) ; 

void *lfind(const void *key, const void *base, size_t *nelp, size_t width,
    int (*compar)(const void *, const void *))
{

	return (lwork(key, base, nelp, width, compar, 0));
}
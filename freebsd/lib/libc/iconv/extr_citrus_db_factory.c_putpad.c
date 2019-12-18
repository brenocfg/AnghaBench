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
struct _region {int dummy; } ;

/* Variables and functions */
 size_t ceilto (size_t) ; 
 int /*<<< orphan*/  put8 (struct _region*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
putpad(struct _region *r, size_t *rofs)
{
	size_t i;

	for (i = ceilto(*rofs) - *rofs; i > 0; i--)
		put8(r, rofs, 0);
}
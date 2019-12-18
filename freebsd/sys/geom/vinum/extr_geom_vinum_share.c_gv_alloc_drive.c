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
struct gv_drive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bzero (struct gv_drive*,int) ; 
 struct gv_drive* g_malloc (int,int /*<<< orphan*/ ) ; 
 struct gv_drive* malloc (int) ; 

struct gv_drive *
gv_alloc_drive(void)
{
	struct gv_drive *d;

#ifdef _KERNEL
	d = g_malloc(sizeof(struct gv_drive), M_NOWAIT);
#else
	d = malloc(sizeof(struct gv_drive));
#endif
	if (d == NULL)
		return (NULL);
	bzero(d, sizeof(struct gv_drive));
	return (d);
}
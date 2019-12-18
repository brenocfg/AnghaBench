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
struct gv_volume {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bzero (struct gv_volume*,int) ; 
 struct gv_volume* g_malloc (int,int /*<<< orphan*/ ) ; 
 struct gv_volume* malloc (int) ; 

struct gv_volume *
gv_alloc_volume(void)
{
	struct gv_volume *v;

#ifdef _KERNEL
	v = g_malloc(sizeof(struct gv_volume), M_NOWAIT);
#else
	v = malloc(sizeof(struct gv_volume));
#endif
	if (v == NULL)
		return (NULL);
	bzero(v, sizeof(struct gv_volume));
	return (v);
}
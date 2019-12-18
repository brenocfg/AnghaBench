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
struct gv_plex {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bzero (struct gv_plex*,int) ; 
 struct gv_plex* g_malloc (int,int /*<<< orphan*/ ) ; 
 struct gv_plex* malloc (int) ; 

struct gv_plex *
gv_alloc_plex(void)
{
	struct gv_plex *p;

#ifdef _KERNEL
	p = g_malloc(sizeof(struct gv_plex), M_NOWAIT);
#else
	p = malloc(sizeof(struct gv_plex));
#endif
	if (p == NULL)
		return (NULL);
	bzero(p, sizeof(struct gv_plex));
	return (p);
}
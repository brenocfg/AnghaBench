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
struct gv_sd {int plex_offset; int size; int drive_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bzero (struct gv_sd*,int) ; 
 struct gv_sd* g_malloc (int,int /*<<< orphan*/ ) ; 
 struct gv_sd* malloc (int) ; 

struct gv_sd *
gv_alloc_sd(void)
{
	struct gv_sd *s;

#ifdef _KERNEL
	s = g_malloc(sizeof(struct gv_sd), M_NOWAIT);
#else
	s = malloc(sizeof(struct gv_sd));
#endif
	if (s == NULL)
		return (NULL);
	bzero(s, sizeof(struct gv_sd));
	s->plex_offset = -1;
	s->size = -1;
	s->drive_offset = -1;
	return (s);
}
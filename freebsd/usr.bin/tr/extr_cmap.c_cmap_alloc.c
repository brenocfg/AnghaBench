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
struct cmap {int cm_havecache; scalar_t__ cm_max; scalar_t__ cm_min; int /*<<< orphan*/  cm_def; int /*<<< orphan*/ * cm_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_DEF_SELF ; 
 struct cmap* malloc (int) ; 

struct cmap *
cmap_alloc(void)
{
	struct cmap *cm;

	cm = malloc(sizeof(*cm));
	if (cm == NULL)
		return (NULL);
	cm->cm_root = NULL;
	cm->cm_def = CM_DEF_SELF;
	cm->cm_havecache = false;
	cm->cm_min = cm->cm_max = 0;
	return (cm);
}
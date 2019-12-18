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
struct cset {int cs_havecache; int cs_invert; int /*<<< orphan*/ * cs_classes; int /*<<< orphan*/ * cs_root; } ;

/* Variables and functions */
 struct cset* malloc (int) ; 

struct cset *
cset_alloc(void)
{
	struct cset *cs;

	if ((cs = malloc(sizeof(*cs))) == NULL)
		return (NULL);
	cs->cs_root = NULL;
	cs->cs_classes = NULL;
	cs->cs_havecache = false;
	cs->cs_invert = false;
	return (cs);
}
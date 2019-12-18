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
typedef  int /*<<< orphan*/  wint_t ;
struct cmap {int cm_havecache; int /*<<< orphan*/  cm_def; } ;

/* Variables and functions */

wint_t
cmap_default(struct cmap *cm, wint_t def)
{
	wint_t old;

	old = cm->cm_def;
	cm->cm_def = def;
	cm->cm_havecache = false;
	return (old);
}
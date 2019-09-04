#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rev_cmdline_info {unsigned int nr; TYPE_1__* rev; int /*<<< orphan*/  alloc; } ;
struct rev_info {struct rev_cmdline_info cmdline; } ;
struct object {int dummy; } ;
struct TYPE_2__ {int whence; unsigned int flags; int /*<<< orphan*/  name; struct object* item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void add_rev_cmdline(struct rev_info *revs,
			    struct object *item,
			    const char *name,
			    int whence,
			    unsigned flags)
{
	struct rev_cmdline_info *info = &revs->cmdline;
	unsigned int nr = info->nr;

	ALLOC_GROW(info->rev, nr + 1, info->alloc);
	info->rev[nr].item = item;
	info->rev[nr].name = xstrdup(name);
	info->rev[nr].whence = whence;
	info->rev[nr].flags = flags;
	info->nr++;
}
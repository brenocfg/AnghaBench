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
struct tag {int dummy; } ;
struct roff_meta {int /*<<< orphan*/ * os; int /*<<< orphan*/ * date; } ;
struct html {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAG_TABLE ; 
 int /*<<< orphan*/  TAG_TD ; 
 int /*<<< orphan*/  TAG_TR ; 
 struct tag* print_otag (struct html*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_stagq (struct html*,struct tag*) ; 
 int /*<<< orphan*/  print_tagq (struct html*,struct tag*) ; 
 int /*<<< orphan*/  print_text (struct html*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
man_root_post(const struct roff_meta *man, struct html *h)
{
	struct tag	*t, *tt;

	t = print_otag(h, TAG_TABLE, "c", "foot");
	tt = print_otag(h, TAG_TR, "");

	print_otag(h, TAG_TD, "c", "foot-date");
	print_text(h, man->date);
	print_stagq(h, tt);

	print_otag(h, TAG_TD, "c", "foot-os");
	if (man->os != NULL)
		print_text(h, man->os);
	print_tagq(h, t);
}
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
struct roff_meta {int /*<<< orphan*/ * msec; int /*<<< orphan*/  title; int /*<<< orphan*/ * arch; int /*<<< orphan*/  vol; } ;
struct html {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAG_TABLE ; 
 int /*<<< orphan*/  TAG_TD ; 
 int /*<<< orphan*/  TAG_TR ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mandoc_asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* mandoc_strdup (int /*<<< orphan*/ ) ; 
 struct tag* print_otag (struct html*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_stagq (struct html*,struct tag*) ; 
 int /*<<< orphan*/  print_tagq (struct html*,struct tag*) ; 
 int /*<<< orphan*/  print_text (struct html*,char*) ; 

__attribute__((used)) static int
mdoc_root_pre(const struct roff_meta *meta, struct html *h)
{
	struct tag	*t, *tt;
	char		*volume, *title;

	if (NULL == meta->arch)
		volume = mandoc_strdup(meta->vol);
	else
		mandoc_asprintf(&volume, "%s (%s)",
		    meta->vol, meta->arch);

	if (NULL == meta->msec)
		title = mandoc_strdup(meta->title);
	else
		mandoc_asprintf(&title, "%s(%s)",
		    meta->title, meta->msec);

	t = print_otag(h, TAG_TABLE, "c", "head");
	tt = print_otag(h, TAG_TR, "");

	print_otag(h, TAG_TD, "c", "head-ltitle");
	print_text(h, title);
	print_stagq(h, tt);

	print_otag(h, TAG_TD, "c", "head-vol");
	print_text(h, volume);
	print_stagq(h, tt);

	print_otag(h, TAG_TD, "c", "head-rtitle");
	print_text(h, title);
	print_tagq(h, t);

	free(title);
	free(volume);
	return 1;
}
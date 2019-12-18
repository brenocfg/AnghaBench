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
struct roff_meta {int /*<<< orphan*/  title; int /*<<< orphan*/ * arch; int /*<<< orphan*/ * msec; } ;
struct html {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAG_TITLE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mandoc_asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 char* mandoc_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_gen_head (struct html*) ; 
 int /*<<< orphan*/  print_otag (struct html*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_text (struct html*,char*) ; 

__attribute__((used)) static void
print_mdoc_head(const struct roff_meta *meta, struct html *h)
{
	char	*cp;

	print_gen_head(h);

	if (meta->arch != NULL && meta->msec != NULL)
		mandoc_asprintf(&cp, "%s(%s) (%s)", meta->title,
		    meta->msec, meta->arch);
	else if (meta->msec != NULL)
		mandoc_asprintf(&cp, "%s(%s)", meta->title, meta->msec);
	else if (meta->arch != NULL)
		mandoc_asprintf(&cp, "%s (%s)", meta->title, meta->arch);
	else
		cp = mandoc_strdup(meta->title);

	print_otag(h, TAG_TITLE, "");
	print_text(h, cp);
	free(cp);
}
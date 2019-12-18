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
struct roff_meta {int /*<<< orphan*/  msec; int /*<<< orphan*/  title; } ;
struct html {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAG_TITLE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mandoc_asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_gen_head (struct html*) ; 
 int /*<<< orphan*/  print_otag (struct html*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_text (struct html*,char*) ; 

__attribute__((used)) static void
print_man_head(const struct roff_meta *man, struct html *h)
{
	char	*cp;

	print_gen_head(h);
	mandoc_asprintf(&cp, "%s(%s)", man->title, man->msec);
	print_otag(h, TAG_TITLE, "");
	print_text(h, cp);
	free(cp);
}
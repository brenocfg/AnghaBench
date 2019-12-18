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
struct ignentry {int /*<<< orphan*/ * mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ignentry*,int /*<<< orphan*/ ) ; 
 struct ignentry* calloc (int,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  ignores ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static void
ignoreadd(const char *mask)
{
	struct ignentry *ign;

	ign = calloc(1, sizeof(*ign));
	if (ign == NULL)
		errx(1, "cannot allocate memory");
	ign->mask = strdup(mask);
	if (ign->mask == NULL)
		errx(1, "cannot allocate memory");
	SLIST_INSERT_HEAD(&ignores, ign, next);
}
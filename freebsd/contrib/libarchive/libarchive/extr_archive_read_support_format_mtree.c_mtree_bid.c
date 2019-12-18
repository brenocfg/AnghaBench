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
struct archive_read {int dummy; } ;

/* Variables and functions */
 char* __archive_read_ahead (struct archive_read*,scalar_t__,int /*<<< orphan*/ *) ; 
 int detect_form (struct archive_read*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char const*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
mtree_bid(struct archive_read *a, int best_bid)
{
	const char *signature = "#mtree";
	const char *p;

	(void)best_bid; /* UNUSED */

	/* Now let's look at the actual header and see if it matches. */
	p = __archive_read_ahead(a, strlen(signature), NULL);
	if (p == NULL)
		return (-1);

	if (memcmp(p, signature, strlen(signature)) == 0)
		return (8 * (int)strlen(signature));

	/*
	 * There is not a mtree signature. Let's try to detect mtree format.
	 */
	return (detect_form(a, NULL));
}
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
struct keytab {int kt_i; int /*<<< orphan*/ * kt_cp; } ;

/* Variables and functions */
 struct keytab* keywords ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

int
keyword(const char *cp)
{
	const struct keytab *kt = keywords;

	while (kt->kt_cp != NULL && strcmp(kt->kt_cp, cp) != 0)
		kt++;
	return (kt->kt_i);
}
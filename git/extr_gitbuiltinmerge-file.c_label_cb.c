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
struct option {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int error (char*) ; 

__attribute__((used)) static int label_cb(const struct option *opt, const char *arg, int unset)
{
	static int label_count = 0;
	const char **names = (const char **)opt->value;

	BUG_ON_OPT_NEG(unset);

	if (label_count >= 3)
		return error("too many labels on the command line");
	names[label_count++] = arg;
	return 0;
}
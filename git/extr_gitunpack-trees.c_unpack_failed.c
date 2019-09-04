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
struct unpack_trees_options {int /*<<< orphan*/  exiting_early; int /*<<< orphan*/  quiet; int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int /*<<< orphan*/  discard_index (int /*<<< orphan*/ *) ; 
 int error (char*,char const*) ; 

__attribute__((used)) static int unpack_failed(struct unpack_trees_options *o, const char *message)
{
	discard_index(&o->result);
	if (!o->quiet && !o->exiting_early) {
		if (message)
			return error("%s", message);
		return -1;
	}
	return -1;
}
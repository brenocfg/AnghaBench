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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ) ; 
 scalar_t__ read_ref_full (char*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int reset_merge (struct object_id*) ; 

__attribute__((used)) static int skip_single_pick(void)
{
	struct object_id head;

	if (read_ref_full("HEAD", 0, &head, NULL))
		return error(_("cannot resolve HEAD"));
	return reset_merge(&head);
}
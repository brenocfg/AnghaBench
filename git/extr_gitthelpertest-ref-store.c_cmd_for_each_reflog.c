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
struct ref_store {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  each_ref ; 
 int refs_for_each_reflog (struct ref_store*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmd_for_each_reflog(struct ref_store *refs, const char **argv)
{
	return refs_for_each_reflog(refs, each_ref, NULL);
}
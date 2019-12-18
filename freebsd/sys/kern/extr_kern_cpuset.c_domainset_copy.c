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
struct domainset {int /*<<< orphan*/  ds_prefer; int /*<<< orphan*/  ds_policy; int /*<<< orphan*/  ds_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAINSET_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
domainset_copy(const struct domainset *from, struct domainset *to)
{

	DOMAINSET_COPY(&from->ds_mask, &to->ds_mask);
	to->ds_policy = from->ds_policy;
	to->ds_prefer = from->ds_prefer;
}
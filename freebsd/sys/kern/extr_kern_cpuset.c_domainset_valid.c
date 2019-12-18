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
struct domainset {scalar_t__ ds_policy; int /*<<< orphan*/  ds_mask; int /*<<< orphan*/  ds_prefer; } ;

/* Variables and functions */
 int DOMAINSET_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ DOMAINSET_POLICY_PREFER ; 
 int DOMAINSET_SUBSET (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
domainset_valid(const struct domainset *parent, const struct domainset *child)
{
	if (child->ds_policy != DOMAINSET_POLICY_PREFER)
		return (DOMAINSET_SUBSET(&parent->ds_mask, &child->ds_mask));
	return (DOMAINSET_ISSET(child->ds_prefer, &parent->ds_mask));
}
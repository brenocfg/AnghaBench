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
struct domainset {scalar_t__ ds_policy; scalar_t__ ds_prefer; int /*<<< orphan*/  ds_mask; } ;

/* Variables and functions */
 scalar_t__ DOMAINSET_CMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
domainset_equal(const struct domainset *one, const struct domainset *two)
{

	return (DOMAINSET_CMP(&one->ds_mask, &two->ds_mask) == 0 &&
	    one->ds_policy == two->ds_policy &&
	    one->ds_prefer == two->ds_prefer);
}
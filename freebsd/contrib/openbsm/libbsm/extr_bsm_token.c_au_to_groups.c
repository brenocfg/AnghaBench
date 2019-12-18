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
typedef  int /*<<< orphan*/  token_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_MAX_GROUPS ; 
 int /*<<< orphan*/ * au_to_newgroups (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

token_t *
au_to_groups(int *groups)
{

	return (au_to_newgroups(AUDIT_MAX_GROUPS, (gid_t *)groups));
}
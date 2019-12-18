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
struct ifvlan {int /*<<< orphan*/  ifv_pcp; int /*<<< orphan*/  ifv_vid; int /*<<< orphan*/  ifv_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVL_MAKETAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vlan_tag_recalculate(struct ifvlan *ifv)
{

       ifv->ifv_tag = EVL_MAKETAG(ifv->ifv_vid, ifv->ifv_pcp, 0);
}
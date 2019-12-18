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
typedef  int /*<<< orphan*/  SRP_user_pwd ;
typedef  int /*<<< orphan*/  SRP_VBASE ;

/* Variables and functions */
 int /*<<< orphan*/ * find_user (int /*<<< orphan*/ *,char*) ; 

SRP_user_pwd *SRP_VBASE_get_by_user(SRP_VBASE *vb, char *username)
{
    return find_user(vb, username);
}
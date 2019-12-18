#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  users_pwd; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SRP_user_pwd ;
typedef  TYPE_2__ SRP_VBASE ;

/* Variables and functions */
 int sk_SRP_user_pwd_num (int /*<<< orphan*/ ) ; 
 TYPE_1__* sk_SRP_user_pwd_value (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static SRP_user_pwd *find_user(SRP_VBASE *vb, char *username)
{
    int i;
    SRP_user_pwd *user;

    if (vb == NULL)
        return NULL;

    for (i = 0; i < sk_SRP_user_pwd_num(vb->users_pwd); i++) {
        user = sk_SRP_user_pwd_value(vb->users_pwd, i);
        if (strcmp(user->id, username) == 0)
            return user;
    }

    return NULL;
}
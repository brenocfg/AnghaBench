#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int len; int /*<<< orphan*/ ** val; } ;
struct TYPE_5__ {TYPE_1__ name_string; } ;
typedef  int /*<<< orphan*/ * Realm ;
typedef  TYPE_2__ PrincipalName ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_TGS_NAME ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Realm
get_krbtgt_realm(const PrincipalName *p)
{
    if(p->name_string.len == 2
       && strcmp(p->name_string.val[0], KRB5_TGS_NAME) == 0)
	return p->name_string.val[1];
    else
	return NULL;
}
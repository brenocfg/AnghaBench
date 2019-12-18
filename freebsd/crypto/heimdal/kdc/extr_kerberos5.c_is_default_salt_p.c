#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ salttype; int /*<<< orphan*/  saltvalue; } ;
typedef  TYPE_2__ krb5_salt ;
typedef  int /*<<< orphan*/  krb5_boolean ;
struct TYPE_8__ {TYPE_1__* salt; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  salt; } ;
typedef  TYPE_3__ Key ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ krb5_data_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_boolean
is_default_salt_p(const krb5_salt *default_salt, const Key *key)
{
    if (key->salt == NULL)
	return TRUE;
    if (default_salt->salttype != key->salt->type)
	return FALSE;
    if (krb5_data_cmp(&default_salt->saltvalue, &key->salt->salt))
	return FALSE;
    return TRUE;
}
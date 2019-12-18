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

/* Variables and functions */
 int /*<<< orphan*/ * context ; 
 int /*<<< orphan*/ * id ; 
 int krb5_afslog (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ *,int,char*,char const*) ; 
 int /*<<< orphan*/  realm ; 
 scalar_t__ use_krb5 ; 

__attribute__((used)) static int
do_afslog(const char *cell)
{
    int k5ret;

    k5ret = 0;

#ifdef KRB5
    if(context != NULL && id != NULL && use_krb5) {
	k5ret = krb5_afslog(context, id, cell, realm);
	if(k5ret == 0)
	    return 0;
    }
#endif
    if (cell == NULL)
	cell = "<default cell>";
#ifdef KRB5
    if (k5ret)
	krb5_warn(context, k5ret, "krb5_afslog(%s)", cell);
#endif
    if (k5ret)
	return 1;
    return 0;
}
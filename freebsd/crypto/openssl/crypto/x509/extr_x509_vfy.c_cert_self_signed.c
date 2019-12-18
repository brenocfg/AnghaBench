#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ex_flags; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int EXFLAG_SS ; 
 int /*<<< orphan*/  X509_check_purpose (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cert_self_signed(X509 *x)
{
    /*
     * FIXME: x509v3_cache_extensions() needs to detect more failures and not
     * set EXFLAG_SET when that happens.  Especially, if the failures are
     * parse errors, rather than memory pressure!
     */
    X509_check_purpose(x, -1, 0);
    if (x->ex_flags & EXFLAG_SS)
        return 1;
    else
        return 0;
}
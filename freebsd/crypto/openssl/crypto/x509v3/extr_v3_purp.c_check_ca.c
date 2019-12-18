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
struct TYPE_4__ {int ex_flags; int ex_nscert; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int EXFLAG_BCONS ; 
 int EXFLAG_CA ; 
 int EXFLAG_KUSAGE ; 
 int EXFLAG_NSCERT ; 
 int /*<<< orphan*/  KU_KEY_CERT_SIGN ; 
 int NS_ANY_CA ; 
 int V1_ROOT ; 
 scalar_t__ ku_reject (TYPE_1__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_ca(const X509 *x)
{
    /* keyUsage if present should allow cert signing */
    if (ku_reject(x, KU_KEY_CERT_SIGN))
        return 0;
    if (x->ex_flags & EXFLAG_BCONS) {
        if (x->ex_flags & EXFLAG_CA)
            return 1;
        /* If basicConstraints says not a CA then say so */
        else
            return 0;
    } else {
        /* we support V1 roots for...  uh, I don't really know why. */
        if ((x->ex_flags & V1_ROOT) == V1_ROOT)
            return 3;
        /*
         * If key usage present it must have certSign so tolerate it
         */
        else if (x->ex_flags & EXFLAG_KUSAGE)
            return 4;
        /* Older certificates could have Netscape-specific CA types */
        else if (x->ex_flags & EXFLAG_NSCERT && x->ex_nscert & NS_ANY_CA)
            return 5;
        /* can this still be regarded a CA certificate?  I doubt it */
        return 0;
    }
}
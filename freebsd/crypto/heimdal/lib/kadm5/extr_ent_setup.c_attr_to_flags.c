#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int postdate; int forwardable; int initial; int renewable; int proxiable; int invalid; int require_preauth; int server; int change_pw; int client; int ok_as_delegate; int trusted_for_delegation; int allow_kerberos4; int allow_digest; } ;
typedef  TYPE_1__ HDBFlags ;

/* Variables and functions */
 unsigned int KRB5_KDB_ALLOW_DIGEST ; 
 unsigned int KRB5_KDB_ALLOW_KERBEROS4 ; 
 unsigned int KRB5_KDB_DISALLOW_ALL_TIX ; 
 unsigned int KRB5_KDB_DISALLOW_FORWARDABLE ; 
 unsigned int KRB5_KDB_DISALLOW_POSTDATED ; 
 unsigned int KRB5_KDB_DISALLOW_PROXIABLE ; 
 unsigned int KRB5_KDB_DISALLOW_RENEWABLE ; 
 unsigned int KRB5_KDB_DISALLOW_SVR ; 
 unsigned int KRB5_KDB_DISALLOW_TGT_BASED ; 
 unsigned int KRB5_KDB_OK_AS_DELEGATE ; 
 unsigned int KRB5_KDB_PWCHANGE_SERVICE ; 
 unsigned int KRB5_KDB_REQUIRES_PRE_AUTH ; 
 unsigned int KRB5_KDB_TRUSTED_FOR_DELEGATION ; 

__attribute__((used)) static void
attr_to_flags(unsigned attr, HDBFlags *flags)
{
    flags->postdate =		!(attr & KRB5_KDB_DISALLOW_POSTDATED);
    flags->forwardable =	!(attr & KRB5_KDB_DISALLOW_FORWARDABLE);
    flags->initial =	       !!(attr & KRB5_KDB_DISALLOW_TGT_BASED);
    flags->renewable =		!(attr & KRB5_KDB_DISALLOW_RENEWABLE);
    flags->proxiable =		!(attr & KRB5_KDB_DISALLOW_PROXIABLE);
    /* DUP_SKEY */
    flags->invalid =	       !!(attr & KRB5_KDB_DISALLOW_ALL_TIX);
    flags->require_preauth =   !!(attr & KRB5_KDB_REQUIRES_PRE_AUTH);
    /* HW_AUTH */
    flags->server =		!(attr & KRB5_KDB_DISALLOW_SVR);
    flags->change_pw = 	       !!(attr & KRB5_KDB_PWCHANGE_SERVICE);
    flags->client =	        1; /* XXX */
    flags->ok_as_delegate =    !!(attr & KRB5_KDB_OK_AS_DELEGATE);
    flags->trusted_for_delegation = !!(attr & KRB5_KDB_TRUSTED_FOR_DELEGATION);
    flags->allow_kerberos4 =   !!(attr & KRB5_KDB_ALLOW_KERBEROS4);
    flags->allow_digest =      !!(attr & KRB5_KDB_ALLOW_DIGEST);
}
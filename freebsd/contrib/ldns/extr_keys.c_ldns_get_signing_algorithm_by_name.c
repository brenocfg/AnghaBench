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
typedef  int /*<<< orphan*/  ldns_signing_algorithm ;
struct TYPE_3__ {char* member_1; int /*<<< orphan*/  id; scalar_t__ name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ldns_lookup_table ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_DH ; 
 int /*<<< orphan*/  LDNS_ECC ; 
 int /*<<< orphan*/  LDNS_INDIRECT ; 
 int /*<<< orphan*/  LDNS_PRIVATEDNS ; 
 int /*<<< orphan*/  LDNS_PRIVATEOID ; 
 int /*<<< orphan*/  LDNS_SIGN_DSA_NSEC3 ; 
 int /*<<< orphan*/  LDNS_SIGN_ECC_GOST ; 
 int /*<<< orphan*/  LDNS_SIGN_HMACMD5 ; 
 int /*<<< orphan*/  LDNS_SIGN_RSASHA1_NSEC3 ; 
 TYPE_1__* ldns_signing_algorithms ; 
 scalar_t__ strcasecmp (scalar_t__,char const*) ; 
 int /*<<< orphan*/  strtol (char const*,char**,int) ; 

ldns_signing_algorithm ldns_get_signing_algorithm_by_name(const char* name)
{
        /* list of (signing algorithm id, alias_name) */
        ldns_lookup_table aliases[] = {
                /* from bind dnssec-keygen */
                {LDNS_SIGN_HMACMD5, "HMAC-MD5"},
                {LDNS_SIGN_DSA_NSEC3, "NSEC3DSA"},
                {LDNS_SIGN_RSASHA1_NSEC3, "NSEC3RSASHA1"},
                /* old ldns usage, now RFC names */
#ifdef USE_DSA
                {LDNS_SIGN_DSA_NSEC3, "DSA_NSEC3" },
#endif
                {LDNS_SIGN_RSASHA1_NSEC3, "RSASHA1_NSEC3" },
#ifdef USE_GOST
                {LDNS_SIGN_ECC_GOST, "GOST"},
#endif
                /* compat with possible output */
                {LDNS_DH, "DH"},
                {LDNS_ECC, "ECC"},
                {LDNS_INDIRECT, "INDIRECT"},
                {LDNS_PRIVATEDNS, "PRIVATEDNS"},
                {LDNS_PRIVATEOID, "PRIVATEOID"},
                {0, NULL}};
        ldns_lookup_table* lt = ldns_signing_algorithms;
	ldns_signing_algorithm a;
	char *endptr;

        while(lt->name) {
                if(strcasecmp(lt->name, name) == 0)
                        return lt->id;
                lt++;
        }
        lt = aliases;
        while(lt->name) {
                if(strcasecmp(lt->name, name) == 0)
                        return lt->id;
                lt++;
        }
	a = strtol(name, &endptr, 10);
	if (*name && !*endptr)
		return a;

        return 0;
}
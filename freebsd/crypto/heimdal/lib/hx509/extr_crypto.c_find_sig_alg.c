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
struct signature_alg {int /*<<< orphan*/  sig_oid; } ;
typedef  int /*<<< orphan*/  heim_oid ;

/* Variables and functions */
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct signature_alg const** sig_algs ; 

__attribute__((used)) static const struct signature_alg *
find_sig_alg(const heim_oid *oid)
{
    unsigned int i;
    for (i = 0; sig_algs[i]; i++)
	if (der_heim_oid_cmp(sig_algs[i]->sig_oid, oid) == 0)
	    return sig_algs[i];
    return NULL;
}
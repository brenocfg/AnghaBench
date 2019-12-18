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
struct TYPE_3__ {int /*<<< orphan*/  _tsig_algorithm; } ;
typedef  TYPE_1__ ldns_resolver ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

void
ldns_resolver_set_tsig_algorithm(ldns_resolver *r, const char *tsig_algorithm)
{
	LDNS_FREE(r->_tsig_algorithm);
	r->_tsig_algorithm = strdup(tsig_algorithm);
}
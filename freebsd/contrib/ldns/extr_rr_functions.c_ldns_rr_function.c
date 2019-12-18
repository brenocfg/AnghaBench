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
typedef  scalar_t__ ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static ldns_rdf *
ldns_rr_function(ldns_rr_type type, const ldns_rr *rr, size_t pos)
{
        if (!rr || ldns_rr_get_type(rr) != type) {
                return NULL;
        }
        return ldns_rr_rdf(rr, pos);
}
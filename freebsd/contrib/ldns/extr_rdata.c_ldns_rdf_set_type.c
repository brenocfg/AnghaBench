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
typedef  int /*<<< orphan*/  ldns_rdf_type ;
struct TYPE_3__ {int /*<<< orphan*/  _type; } ;
typedef  TYPE_1__ ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
ldns_rdf_set_type(ldns_rdf *rd, ldns_rdf_type type)
{
	assert(rd != NULL);
	rd->_type = type;
}
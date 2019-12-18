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
struct TYPE_4__ {struct TYPE_4__* _data; } ;
typedef  TYPE_1__ ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (TYPE_1__*) ; 

void
ldns_rdf_deep_free(ldns_rdf *rd)
{
	if (rd) {
		if (rd->_data) {
			LDNS_FREE(rd->_data);
		}
		LDNS_FREE(rd);
	}
}
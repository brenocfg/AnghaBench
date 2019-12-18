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
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_SECTION_ANY ; 
 scalar_t__ ldns_pkt_section_count (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool
ldns_pkt_empty(ldns_pkt *p)
{
	if (!p) {
		return true; /* NULL is empty? */
	}
	if (ldns_pkt_section_count(p, LDNS_SECTION_ANY) > 0) {
		return false;
	} else {
		return true;
    }
}
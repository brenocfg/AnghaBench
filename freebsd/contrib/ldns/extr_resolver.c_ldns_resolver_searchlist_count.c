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
struct TYPE_3__ {size_t _searchlist_count; } ;
typedef  TYPE_1__ ldns_resolver ;

/* Variables and functions */

size_t
ldns_resolver_searchlist_count(const ldns_resolver *r)
{
	return r->_searchlist_count;
}
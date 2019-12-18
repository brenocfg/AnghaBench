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
struct timeval {int dummy; } ;
struct TYPE_3__ {struct timeval _timeout; } ;
typedef  TYPE_1__ ldns_resolver ;

/* Variables and functions */

struct timeval
ldns_resolver_timeout(const ldns_resolver *r)
{
	return r->_timeout;
}
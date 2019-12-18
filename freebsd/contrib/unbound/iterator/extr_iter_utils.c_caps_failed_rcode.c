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
struct reply_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ FLAGS_GET_RCODE (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RCODE_NXDOMAIN ; 

int caps_failed_rcode(struct reply_info* rep)
{
	return !(FLAGS_GET_RCODE(rep->flags) == LDNS_RCODE_NOERROR ||
		FLAGS_GET_RCODE(rep->flags) == LDNS_RCODE_NXDOMAIN);
}
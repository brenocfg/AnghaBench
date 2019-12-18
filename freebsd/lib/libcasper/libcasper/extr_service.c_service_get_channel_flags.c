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
struct service {scalar_t__ s_magic; int s_flags; } ;

/* Variables and functions */
 int CASPER_NO_UNIQ ; 
 int CASPER_SERVICE_NO_UNIQ_LIMITS ; 
 scalar_t__ SERVICE_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 

int
service_get_channel_flags(struct service *service)
{
	int flags;

	assert(service->s_magic == SERVICE_MAGIC);
	flags = 0;

	if ((service->s_flags & CASPER_SERVICE_NO_UNIQ_LIMITS) != 0)
		flags |= CASPER_NO_UNIQ;

	return (flags);
}
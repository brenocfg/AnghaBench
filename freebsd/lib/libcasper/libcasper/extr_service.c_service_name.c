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
struct service {scalar_t__ s_magic; char const* s_name; } ;

/* Variables and functions */
 scalar_t__ SERVICE_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 

const char *
service_name(struct service *service)
{

	assert(service->s_magic == SERVICE_MAGIC);
	return (service->s_name);
}
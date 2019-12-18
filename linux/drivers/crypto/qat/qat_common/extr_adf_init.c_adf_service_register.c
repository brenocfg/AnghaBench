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
struct service_hndl {int /*<<< orphan*/  start_status; int /*<<< orphan*/  init_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  adf_service_add (struct service_hndl*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int adf_service_register(struct service_hndl *service)
{
	memset(service->init_status, 0, sizeof(service->init_status));
	memset(service->start_status, 0, sizeof(service->start_status));
	adf_service_add(service);
	return 0;
}
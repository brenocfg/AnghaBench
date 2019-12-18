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
struct sema {int dummy; } ;

/* Variables and functions */
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  sema_destroy (struct sema*) ; 

int os_destroy_semaphore(struct sema *sema)
{
    sema_destroy(sema);
    return PQI_STATUS_SUCCESS;

}
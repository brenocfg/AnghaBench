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
struct receive_sa {int dummy; } ;

/* Variables and functions */
 int wpa_drv_set_receive_lowest_pn (void*,struct receive_sa*) ; 

__attribute__((used)) static int wpas_set_receive_lowest_pn(void *wpa_s, struct receive_sa *sa)
{
	return wpa_drv_set_receive_lowest_pn(wpa_s, sa);
}
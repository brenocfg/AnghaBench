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
struct gnss_serial {void* drvdata; } ;

/* Variables and functions */

__attribute__((used)) static inline void *gnss_serial_get_drvdata(struct gnss_serial *gserial)
{
	return gserial->drvdata;
}
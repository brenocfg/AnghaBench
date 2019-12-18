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
struct TYPE_3__ {scalar_t__ offset; scalar_t__ length; int* buffer; int checksum; } ;
typedef  TYPE_1__ vpdbuf_t ;

/* Variables and functions */

__attribute__((used)) static inline int
vpdnext(vpdbuf_t *vpd)
{
	int rc = -1;
	if (vpd->offset < vpd->length) {
		rc = vpd->buffer[vpd->offset++];
		vpd->checksum += rc;
	}
	return rc;
}
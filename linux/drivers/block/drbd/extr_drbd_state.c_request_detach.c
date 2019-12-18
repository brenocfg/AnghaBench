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
struct drbd_device {int dummy; } ;
typedef  enum drbd_state_rv { ____Placeholder_drbd_state_rv } drbd_state_rv ;

/* Variables and functions */
 int CS_INHIBIT_MD_IO ; 
 int CS_ORDERED ; 
 int CS_VERBOSE ; 
 int /*<<< orphan*/  D_FAILED ; 
 int /*<<< orphan*/  NS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk ; 
 int drbd_req_state (struct drbd_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum drbd_state_rv
request_detach(struct drbd_device *device)
{
	return drbd_req_state(device, NS(disk, D_FAILED),
			CS_VERBOSE | CS_ORDERED | CS_INHIBIT_MD_IO);
}
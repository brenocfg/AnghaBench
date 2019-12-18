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
struct libusb_container_id_descriptor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct libusb_container_id_descriptor*) ; 

void
libusb_free_container_id_descriptor(
    struct libusb_container_id_descriptor *container_id)
{

	free(container_id);
}
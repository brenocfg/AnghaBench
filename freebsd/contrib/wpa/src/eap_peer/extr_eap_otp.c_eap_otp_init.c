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
struct eap_sm {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void * eap_otp_init(struct eap_sm *sm)
{
	/* No need for private data. However, must return non-NULL to indicate
	 * success. */
	return (void *) 1;
}
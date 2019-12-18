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
struct aldap_message {scalar_t__ msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ber_free_elements (scalar_t__) ; 
 int /*<<< orphan*/  free (struct aldap_message*) ; 

void
aldap_freemsg(struct aldap_message *msg)
{
	if (msg->msg)
		ber_free_elements(msg->msg);
	free(msg);
}
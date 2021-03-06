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
struct eap_sm {int /*<<< orphan*/ * identity; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 

void eap_server_clear_identity(struct eap_sm *sm)
{
	os_free(sm->identity);
	sm->identity = NULL;
}
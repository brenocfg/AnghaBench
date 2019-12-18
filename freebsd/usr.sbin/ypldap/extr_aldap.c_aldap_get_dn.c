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
struct aldap_message {int /*<<< orphan*/ * dn; } ;

/* Variables and functions */
 int ber_get_string (int /*<<< orphan*/ *,char**) ; 
 char* utoa (char*) ; 

char *
aldap_get_dn(struct aldap_message *msg)
{
	char *dn;

	if (msg->dn == NULL)
		return NULL;

	if (ber_get_string(msg->dn, &dn) == -1)
		return NULL;

	return utoa(dn);
}
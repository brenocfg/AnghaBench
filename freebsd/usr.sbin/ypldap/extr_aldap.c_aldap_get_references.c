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
struct aldap_message {int /*<<< orphan*/ * references; } ;

/* Variables and functions */
 char** aldap_get_stringset (int /*<<< orphan*/ *) ; 

char **
aldap_get_references(struct aldap_message *msg)
{
	if (msg->references == NULL)
		return NULL;
	return aldap_get_stringset(msg->references);
}
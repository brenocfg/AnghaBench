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

/* Variables and functions */
 int UserNameRequested ; 
 int /*<<< orphan*/  free (int) ; 
 int strdup (char const*) ; 

void
auth_encrypt_user(const char *name)
{
    if (UserNameRequested)
	free(UserNameRequested);
    UserNameRequested = name ? strdup(name) : 0;
}
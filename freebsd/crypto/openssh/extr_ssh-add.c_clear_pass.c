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
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pass ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clear_pass(void)
{
	if (pass) {
		explicit_bzero(pass, strlen(pass));
		free(pass);
		pass = NULL;
	}
}
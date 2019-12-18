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
typedef  int /*<<< orphan*/  pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  FREE (void*) ; 
 int /*<<< orphan*/  RETURNV () ; 

void
openpam_free_data(pam_handle_t *pamh,
	void *data,
	int status)
{

	ENTER();
	(void)pamh;
	(void)status;
	FREE(data);
	RETURNV();
}
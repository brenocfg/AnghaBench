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
struct radius_das_data {scalar_t__ sock; struct radius_das_data* shared_secret; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (scalar_t__) ; 
 int /*<<< orphan*/  os_free (struct radius_das_data*) ; 

void radius_das_deinit(struct radius_das_data *das)
{
	if (das == NULL)
		return;

	if (das->sock >= 0) {
		eloop_unregister_read_sock(das->sock);
		close(das->sock);
	}

	os_free(das->shared_secret);
	os_free(das);
}
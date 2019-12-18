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
struct archive {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static const char *
callback2(struct archive *a, void *_client_data)
{
	int *cd = (int *)_client_data;

	(void)a; /* UNUSED */

	if (*cd == 0) {
		*cd = 1;
		return ("passCallBack");
	}
	return (NULL);
}
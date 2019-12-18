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
 unsigned int GIT_STATUS_WT_DELETED ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int cb_status__check_592(const char *p, unsigned int s, void *payload)
{
	if (s != GIT_STATUS_WT_DELETED ||
		(payload != NULL && strcmp(p, (const char *)payload) != 0))
		return -1;

	return 0;
}
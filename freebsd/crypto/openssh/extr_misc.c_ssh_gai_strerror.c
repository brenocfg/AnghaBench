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
 int EAI_SYSTEM ; 
 scalar_t__ errno ; 
 char const* gai_strerror (int) ; 
 char const* strerror (scalar_t__) ; 

const char *
ssh_gai_strerror(int gaierr)
{
	if (gaierr == EAI_SYSTEM && errno != 0)
		return strerror(errno);
	return gai_strerror(gaierr);
}
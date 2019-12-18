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
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static inline int OK_id(char *s)
{
	return  memcmp (s, "GEM", 3) == 0 || memcmp (s, "BGM", 3) == 0 ||
		memcmp (s, "LNX", 3) == 0 || memcmp (s, "SWP", 3) == 0 ||
		memcmp (s, "RAW", 3) == 0 ;
}
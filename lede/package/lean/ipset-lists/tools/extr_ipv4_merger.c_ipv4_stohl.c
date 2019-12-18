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
typedef  int u32 ;

/* Variables and functions */
 int sscanf (char const*,char*,int*,int*,int*,int*) ; 

__attribute__((used)) static inline u32 ipv4_stohl(const char *s)
{
	int u[4];
	if (sscanf(s, "%d.%d.%d.%d", &u[0], &u[1], &u[2], &u[3]) == 4) {
		return  (((u32)u[0] & 0xff) << 24) |
				(((u32)u[1] & 0xff) << 16) |
				(((u32)u[2] & 0xff) << 8) |
				(((u32)u[3] & 0xff));
	} else
		return 0xffffffff;
}
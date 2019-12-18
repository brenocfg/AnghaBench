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
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 

__attribute__((used)) static inline char *ipv4_hltos(u32 u, char *s)
{
	static char ss[20];
	if (!s)
		s = ss;
	sprintf(s, "%d.%d.%d.%d",
		(int)(u >> 24) & 0xff, (int)(u >> 16) & 0xff,
		(int)(u >> 8) & 0xff, (int)u & 0xff );
	return s;
}
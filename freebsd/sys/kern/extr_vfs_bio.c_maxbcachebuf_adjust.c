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
 int MAXBCACHEBUF ; 
 int MAXBSIZE ; 
 int MAXPHYS ; 
 scalar_t__ bootverbose ; 
 int maxbcachebuf ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
maxbcachebuf_adjust(void)
{
	int i;

	/*
	 * maxbcachebuf must be a power of 2 >= MAXBSIZE.
	 */
	i = 2;
	while (i * 2 <= maxbcachebuf)
		i *= 2;
	maxbcachebuf = i;
	if (maxbcachebuf < MAXBSIZE)
		maxbcachebuf = MAXBSIZE;
	if (maxbcachebuf > MAXPHYS)
		maxbcachebuf = MAXPHYS;
	if (bootverbose != 0 && maxbcachebuf != MAXBCACHEBUF)
		printf("maxbcachebuf=%d\n", maxbcachebuf);
}
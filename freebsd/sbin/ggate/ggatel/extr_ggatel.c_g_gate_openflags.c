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
 unsigned int G_GATE_FLAG_READONLY ; 
 unsigned int G_GATE_FLAG_WRITEONLY ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_WRONLY ; 

__attribute__((used)) static int
g_gate_openflags(unsigned ggflags)
{

	if ((ggflags & G_GATE_FLAG_READONLY) != 0)
		return (O_RDONLY);
	else if ((ggflags & G_GATE_FLAG_WRITEONLY) != 0)
		return (O_WRONLY);
	return (O_RDWR);
}
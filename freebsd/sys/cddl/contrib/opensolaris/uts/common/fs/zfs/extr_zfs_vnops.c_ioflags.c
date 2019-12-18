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
 int FAPPEND ; 
 int FDSYNC ; 
 int FNONBLOCK ; 
 int FRSYNC ; 
 int FSYNC ; 
 int IO_APPEND ; 
 int IO_NDELAY ; 
 int IO_SYNC ; 

__attribute__((used)) static int
ioflags(int ioflags)
{
	int flags = 0;

	if (ioflags & IO_APPEND)
		flags |= FAPPEND;
	if (ioflags & IO_NDELAY)
		flags |= FNONBLOCK;
	if (ioflags & IO_SYNC)
		flags |= (FSYNC | FDSYNC | FRSYNC);

	return (flags);
}
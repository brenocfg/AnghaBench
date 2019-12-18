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
 int /*<<< orphan*/  printf (char*,int,int,unsigned int,int,unsigned int,int) ; 
 int ptrace (int,int,int*,int,int*) ; 

__attribute__((used)) static int
rs6000_ptrace32 (int req, int id, int *addr, int data, int *buf)
{
  int ret = ptrace (req, id, (int *)addr, data, buf);
#if 0
  printf ("rs6000_ptrace32 (%d, %d, 0x%x, %08x, 0x%x) = 0x%x\n",
	  req, id, (unsigned int)addr, data, (unsigned int)buf, ret);
#endif
  return ret;
}
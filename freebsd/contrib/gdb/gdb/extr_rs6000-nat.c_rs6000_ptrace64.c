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
 int /*<<< orphan*/  printf (char*,int,int,long long,int,unsigned int,int) ; 
 int ptracex (int,int,long long,int,int*) ; 

__attribute__((used)) static int
rs6000_ptrace64 (int req, int id, long long addr, int data, int *buf)
{
#ifdef ARCH3264
  int ret = ptracex (req, id, addr, data, buf);
#else
  int ret = 0;
#endif
#if 0
  printf ("rs6000_ptrace64 (%d, %d, 0x%llx, %08x, 0x%x) = 0x%x\n",
	  req, id, addr, data, (unsigned int)buf, ret);
#endif
  return ret;
}
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
struct ViceIoctl {int dummy; } ;

/* Variables and functions */
 int lpioctl (char*,int,struct ViceIoctl*,int) ; 

int
aix_pioctl(char *a_path,
	   int o_opcode,
	   struct ViceIoctl *a_paramsP,
	   int a_followSymlinks)
{
    return lpioctl(a_path, o_opcode, a_paramsP, a_followSymlinks);
}
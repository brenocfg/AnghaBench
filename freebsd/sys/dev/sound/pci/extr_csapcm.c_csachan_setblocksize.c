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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int CS461x_BUFFSIZE ; 

__attribute__((used)) static u_int32_t
csachan_setblocksize(kobj_t obj, void *data, u_int32_t blocksize)
{
	return CS461x_BUFFSIZE / 2;
}
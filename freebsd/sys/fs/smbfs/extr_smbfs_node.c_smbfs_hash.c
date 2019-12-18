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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  FNV1_32_INIT ; 
 int /*<<< orphan*/  fnv_32_buf (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

u_int32_t __inline
smbfs_hash(const u_char *name, int nmlen)
{
	return (fnv_32_buf(name, nmlen, FNV1_32_INIT)); 
}
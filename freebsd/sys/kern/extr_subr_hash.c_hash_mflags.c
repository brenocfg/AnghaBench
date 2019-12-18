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
 int HASH_NOWAIT ; 
 int M_NOWAIT ; 
 int M_WAITOK ; 

__attribute__((used)) static __inline int
hash_mflags(int flags)
{

	return ((flags & HASH_NOWAIT) ? M_NOWAIT : M_WAITOK);
}
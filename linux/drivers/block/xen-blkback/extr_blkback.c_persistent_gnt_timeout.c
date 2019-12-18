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
struct persistent_gnt {int last_used; } ;

/* Variables and functions */
 int HZ ; 
 int jiffies ; 
 int xen_blkif_pgrant_timeout ; 

__attribute__((used)) static inline bool persistent_gnt_timeout(struct persistent_gnt *persistent_gnt)
{
	return xen_blkif_pgrant_timeout &&
	       (jiffies - persistent_gnt->last_used >=
		HZ * xen_blkif_pgrant_timeout);
}
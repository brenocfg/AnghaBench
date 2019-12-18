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
struct mbuf {int dummy; } ;

/* Variables and functions */
 int newnfs_realign (struct mbuf**,int) ; 

int
fhanew_realign(struct mbuf **mb, int malloc_flags)
{
	return (newnfs_realign(mb, malloc_flags));
}
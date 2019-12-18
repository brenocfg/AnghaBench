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
struct mdesc_mem_ops {struct mdesc_handle* (* alloc ) (unsigned int) ;} ;
struct mdesc_handle {struct mdesc_mem_ops* mops; } ;

/* Variables and functions */
 struct mdesc_handle* stub1 (unsigned int) ; 

__attribute__((used)) static struct mdesc_handle *mdesc_alloc(unsigned int mdesc_size,
					struct mdesc_mem_ops *mops)
{
	struct mdesc_handle *hp = mops->alloc(mdesc_size);

	if (hp)
		hp->mops = mops;

	return hp;
}
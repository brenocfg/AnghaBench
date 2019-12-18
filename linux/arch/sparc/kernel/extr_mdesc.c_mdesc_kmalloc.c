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
struct mdesc_hdr {int dummy; } ;
struct mdesc_handle {int dummy; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int __GFP_RETRY_MAYFAIL ; 
 void* kmalloc (unsigned int,int) ; 
 int /*<<< orphan*/  mdesc_handle_init (struct mdesc_handle*,unsigned int,void*) ; 

__attribute__((used)) static struct mdesc_handle *mdesc_kmalloc(unsigned int mdesc_size)
{
	unsigned int handle_size;
	struct mdesc_handle *hp;
	unsigned long addr;
	void *base;

	handle_size = (sizeof(struct mdesc_handle) -
		       sizeof(struct mdesc_hdr) +
		       mdesc_size);
	base = kmalloc(handle_size + 15, GFP_KERNEL | __GFP_RETRY_MAYFAIL);
	if (!base)
		return NULL;

	addr = (unsigned long)base;
	addr = (addr + 15UL) & ~15UL;
	hp = (struct mdesc_handle *) addr;

	mdesc_handle_init(hp, handle_size, base);

	return hp;
}
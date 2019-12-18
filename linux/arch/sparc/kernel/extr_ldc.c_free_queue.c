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
struct ldc_packet {int dummy; } ;

/* Variables and functions */
 unsigned long LDC_PACKET_SIZE ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned long) ; 
 unsigned long get_order (unsigned long) ; 

__attribute__((used)) static void free_queue(unsigned long num_entries, struct ldc_packet *q)
{
	unsigned long size, order;

	if (!q)
		return;

	size = num_entries * LDC_PACKET_SIZE;
	order = get_order(size);

	free_pages((unsigned long)q, order);
}
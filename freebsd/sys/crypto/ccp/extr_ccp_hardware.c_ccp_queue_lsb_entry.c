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
typedef  unsigned int uint8_t ;
struct ccp_queue {int private_lsb; } ;

/* Variables and functions */
 int LSB_REGION_LENGTH ; 

__attribute__((used)) static inline uint8_t
ccp_queue_lsb_entry(struct ccp_queue *qp, unsigned lsb_entry)
{
	return ((qp->private_lsb * LSB_REGION_LENGTH + lsb_entry));
}
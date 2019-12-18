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
 unsigned int KYBER_DISCARD ; 
 unsigned int KYBER_OTHER ; 
 unsigned int KYBER_READ ; 
 unsigned int KYBER_WRITE ; 
#define  REQ_OP_DISCARD 130 
 unsigned int REQ_OP_MASK ; 
#define  REQ_OP_READ 129 
#define  REQ_OP_WRITE 128 

__attribute__((used)) static unsigned int kyber_sched_domain(unsigned int op)
{
	switch (op & REQ_OP_MASK) {
	case REQ_OP_READ:
		return KYBER_READ;
	case REQ_OP_WRITE:
		return KYBER_WRITE;
	case REQ_OP_DISCARD:
		return KYBER_DISCARD;
	default:
		return KYBER_OTHER;
	}
}
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
typedef  int uint8_t ;
struct ena_admin_sq {int sq_identity; } ;

/* Variables and functions */
 int ENA_ADMIN_SQ_SQ_DIRECTION_MASK ; 
 int ENA_ADMIN_SQ_SQ_DIRECTION_SHIFT ; 

__attribute__((used)) static inline void set_ena_admin_sq_sq_direction(struct ena_admin_sq *p, uint8_t val)
{
	p->sq_identity |= (val << ENA_ADMIN_SQ_SQ_DIRECTION_SHIFT) & ENA_ADMIN_SQ_SQ_DIRECTION_MASK;
}
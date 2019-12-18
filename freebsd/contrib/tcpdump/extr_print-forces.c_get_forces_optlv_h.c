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
typedef  size_t uint16_t ;
struct optlv_h {int dummy; } ;

/* Variables and functions */
 size_t F_OP_MAX ; 
 size_t F_OP_RSV ; 
 struct optlv_h const* OPTLV_msg ; 

__attribute__((used)) static inline const struct optlv_h *get_forces_optlv_h(uint16_t opt)
{
	if (opt > F_OP_MAX || opt <= F_OP_RSV)
		return &OPTLV_msg[F_OP_RSV];

	return &OPTLV_msg[opt];
}
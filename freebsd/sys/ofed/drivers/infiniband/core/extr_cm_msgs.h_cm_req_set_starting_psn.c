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
struct cm_req_msg {int /*<<< orphan*/  offset44; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

__attribute__((used)) static inline void cm_req_set_starting_psn(struct cm_req_msg *req_msg,
					   __be32 starting_psn)
{
	req_msg->offset44 = cpu_to_be32((be32_to_cpu(starting_psn) << 8) |
			    (be32_to_cpu(req_msg->offset44) & 0x000000FF));
}
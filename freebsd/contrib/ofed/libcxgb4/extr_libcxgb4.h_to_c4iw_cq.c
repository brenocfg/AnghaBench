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
struct ibv_cq {int dummy; } ;
struct c4iw_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cq ; 
 struct c4iw_cq* to_c4iw_xxx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct c4iw_cq *to_c4iw_cq(struct ibv_cq *ibcq)
{
	return to_c4iw_xxx(cq, cq);
}
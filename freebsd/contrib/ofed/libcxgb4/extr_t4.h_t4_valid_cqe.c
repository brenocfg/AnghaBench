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
struct t4_cqe {int dummy; } ;
struct t4_cq {scalar_t__ gen; } ;

/* Variables and functions */
 scalar_t__ CQE_GENBIT (struct t4_cqe*) ; 

__attribute__((used)) static inline int t4_valid_cqe(struct t4_cq *cq, struct t4_cqe *cqe)
{
	return (CQE_GENBIT(cqe) == cq->gen);
}
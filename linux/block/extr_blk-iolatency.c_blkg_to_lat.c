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
struct iolatency_grp {int dummy; } ;
struct blkcg_gq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blkcg_policy_iolatency ; 
 int /*<<< orphan*/  blkg_to_pd (struct blkcg_gq*,int /*<<< orphan*/ *) ; 
 struct iolatency_grp* pd_to_lat (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct iolatency_grp *blkg_to_lat(struct blkcg_gq *blkg)
{
	return pd_to_lat(blkg_to_pd(blkg, &blkcg_policy_iolatency));
}
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
struct mlx4_pd {int dummy; } ;
struct ibv_pd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pd ; 
 struct mlx4_pd* to_mxxx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mlx4_pd *to_mpd(struct ibv_pd *ibpd)
{
	return to_mxxx(pd, pd);
}
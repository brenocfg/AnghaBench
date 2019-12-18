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
typedef  int /*<<< orphan*/  uint32_t ;
struct rpc_gss_data {int /*<<< orphan*/  gd_lock; int /*<<< orphan*/  gd_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t
rpc_gss_alloc_seq(struct rpc_gss_data *gd)
{
	uint32_t seq;

	mtx_lock(&gd->gd_lock);
	seq = gd->gd_seq;
	gd->gd_seq++;
	mtx_unlock(&gd->gd_lock);

	return (seq);
}
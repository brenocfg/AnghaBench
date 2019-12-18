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
struct socket_hhook_data {void* hctx; int status; int /*<<< orphan*/ * m; struct socket* so; } ;
struct socket {int /*<<< orphan*/  osd; int /*<<< orphan*/  so_vnet; } ;
typedef  size_t int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HHOOKS_RUN_IF (int /*<<< orphan*/ ,struct socket_hhook_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * V_socket_hhh ; 

__attribute__((used)) static int inline
hhook_run_socket(struct socket *so, void *hctx, int32_t h_id)
{
	struct socket_hhook_data hhook_data = {
		.so = so,
		.hctx = hctx,
		.m = NULL,
		.status = 0
	};

	CURVNET_SET(so->so_vnet);
	HHOOKS_RUN_IF(V_socket_hhh[h_id], &hhook_data, &so->osd);
	CURVNET_RESTORE();

	/* Ugly but needed, since hhooks return void for now */
	return (hhook_data.status);
}
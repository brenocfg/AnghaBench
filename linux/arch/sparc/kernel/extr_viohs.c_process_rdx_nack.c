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
struct vio_rdx {int dummy; } ;
struct vio_driver_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 int handshake_failure (struct vio_driver_state*) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int process_rdx_nack(struct vio_driver_state *vio, struct vio_rdx *pkt)
{
	viodbg(HS, "GOT RDX NACK\n");

	return handshake_failure(vio);
}
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
struct vmxnet3_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmxnet3_free_mcast_table (struct vmxnet3_softc*) ; 
 int /*<<< orphan*/  vmxnet3_free_shared_data (struct vmxnet3_softc*) ; 

__attribute__((used)) static void
vmxnet3_free_data(struct vmxnet3_softc *sc)
{

	vmxnet3_free_mcast_table(sc);
	vmxnet3_free_shared_data(sc);
}
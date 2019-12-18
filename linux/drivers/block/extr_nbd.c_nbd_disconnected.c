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
struct nbd_config {int /*<<< orphan*/  runtime_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBD_RT_DISCONNECTED ; 
 int /*<<< orphan*/  NBD_RT_DISCONNECT_REQUESTED ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nbd_disconnected(struct nbd_config *config)
{
	return test_bit(NBD_RT_DISCONNECTED, &config->runtime_flags) ||
		test_bit(NBD_RT_DISCONNECT_REQUESTED, &config->runtime_flags);
}
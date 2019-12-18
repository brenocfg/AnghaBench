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
struct rendezvous_entry {int dummy; } ;
typedef  enum rendezvous_op { ____Placeholder_rendezvous_op } rendezvous_op ;

/* Variables and functions */

__attribute__((used)) static int
mdioproxy_rendezvous_callback(enum rendezvous_op op, struct rendezvous_entry *rendezvous)
{
	return (0);
}
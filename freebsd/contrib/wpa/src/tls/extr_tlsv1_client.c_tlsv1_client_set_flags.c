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
struct tlsv1_client {unsigned int flags; } ;

/* Variables and functions */

void tlsv1_client_set_flags(struct tlsv1_client *conn, unsigned int flags)
{
	conn->flags = flags;
}
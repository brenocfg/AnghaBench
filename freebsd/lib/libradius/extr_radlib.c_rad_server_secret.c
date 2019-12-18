#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rad_handle {size_t srv; TYPE_1__* servers; } ;
struct TYPE_2__ {char const* secret; } ;

/* Variables and functions */

const char *
rad_server_secret(struct rad_handle *h)
{
	return (h->servers[h->srv].secret);
}
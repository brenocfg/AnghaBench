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
struct ngr_checksum {scalar_t__ c1; scalar_t__ c0; } ;

/* Variables and functions */

__attribute__((used)) static inline void
netgear_checksum_init (struct ngr_checksum * c)
{
	c->c0 = c->c1 = 0;
}
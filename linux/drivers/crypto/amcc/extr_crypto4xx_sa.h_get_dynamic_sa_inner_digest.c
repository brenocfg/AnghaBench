#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int key_size; } ;
struct TYPE_4__ {TYPE_1__ bf; } ;
struct dynamic_sa_ctl {TYPE_2__ sa_contents; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */

__attribute__((used)) static inline __le32 *get_dynamic_sa_inner_digest(struct dynamic_sa_ctl *cts)
{
	return (__le32 *) ((unsigned long)cts +
		sizeof(struct dynamic_sa_ctl) +
		cts->sa_contents.bf.key_size * 4);
}
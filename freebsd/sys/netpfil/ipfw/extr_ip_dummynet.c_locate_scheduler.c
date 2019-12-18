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
struct dn_schk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  schedhash; } ;

/* Variables and functions */
 TYPE_1__ dn_cfg ; 
 struct dn_schk* dn_ht_find (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct dn_schk *
locate_scheduler(int i)
{
	return dn_ht_find(dn_cfg.schedhash, i, 0, NULL);
}
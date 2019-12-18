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
struct jmicron_raid_conf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MD_JMICRON ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct jmicron_raid_conf* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct jmicron_raid_conf*,struct jmicron_raid_conf*,int) ; 

__attribute__((used)) static struct jmicron_raid_conf *
jmicron_meta_copy(struct jmicron_raid_conf *meta)
{
	struct jmicron_raid_conf *nmeta;

	nmeta = malloc(sizeof(*meta), M_MD_JMICRON, M_WAITOK);
	memcpy(nmeta, meta, sizeof(*meta));
	return (nmeta);
}
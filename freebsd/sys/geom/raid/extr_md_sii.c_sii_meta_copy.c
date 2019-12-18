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
struct sii_raid_conf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MD_SII ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct sii_raid_conf* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sii_raid_conf*,struct sii_raid_conf*,int) ; 

__attribute__((used)) static struct sii_raid_conf *
sii_meta_copy(struct sii_raid_conf *meta)
{
	struct sii_raid_conf *nmeta;

	nmeta = malloc(sizeof(*meta), M_MD_SII, M_WAITOK);
	memcpy(nmeta, meta, sizeof(*meta));
	return (nmeta);
}
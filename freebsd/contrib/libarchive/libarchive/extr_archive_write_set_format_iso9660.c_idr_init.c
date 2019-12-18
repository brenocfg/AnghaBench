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
struct vdd {scalar_t__ vdd_type; } ;
struct TYPE_2__ {int iso_level; } ;
struct iso9660 {TYPE_1__ opt; } ;
struct idr {int /*<<< orphan*/  char_map; scalar_t__ pool_size; int /*<<< orphan*/ * idrent_pool; } ;

/* Variables and functions */
 scalar_t__ VDD_JOLIET ; 
 int /*<<< orphan*/  d1_characters_map ; 
 int /*<<< orphan*/  d_characters_map ; 
 int /*<<< orphan*/  idr_relaxed_filenames (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
idr_init(struct iso9660 *iso9660, struct vdd *vdd, struct idr *idr)
{

	idr->idrent_pool = NULL;
	idr->pool_size = 0;
	if (vdd->vdd_type != VDD_JOLIET) {
		if (iso9660->opt.iso_level <= 3) {
			memcpy(idr->char_map, d_characters_map,
			    sizeof(idr->char_map));
		} else {
			memcpy(idr->char_map, d1_characters_map,
			    sizeof(idr->char_map));
			idr_relaxed_filenames(idr->char_map);
		}
	}
}
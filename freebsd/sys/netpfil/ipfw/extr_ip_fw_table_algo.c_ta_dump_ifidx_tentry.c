#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct table_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct ifentry {int /*<<< orphan*/  value; TYPE_1__ no; } ;
struct TYPE_6__ {int /*<<< orphan*/  kidx; } ;
struct TYPE_7__ {int masklen; TYPE_2__ v; int /*<<< orphan*/  k; } ;
typedef  TYPE_3__ ipfw_obj_tentry ;

/* Variables and functions */
 int IF_NAMESIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ta_dump_ifidx_tentry(void *ta_state, struct table_info *ti, void *e,
    ipfw_obj_tentry *tent)
{
	struct ifentry *ife;

	ife = (struct ifentry *)e;

	tent->masklen = 8 * IF_NAMESIZE;
	memcpy(&tent->k, ife->no.name, IF_NAMESIZE);
	tent->v.kidx = ife->value;

	return (0);
}
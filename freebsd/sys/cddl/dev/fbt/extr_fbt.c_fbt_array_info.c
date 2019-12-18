#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_12__ {scalar_t__ ctftab; } ;
typedef  TYPE_1__ linker_ctf_t ;
struct TYPE_13__ {int /*<<< orphan*/  ctt_info; } ;
typedef  TYPE_2__ ctf_type_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
struct TYPE_14__ {int /*<<< orphan*/  cth_version; } ;
typedef  TYPE_3__ ctf_header_t ;
struct TYPE_15__ {int /*<<< orphan*/  cta_nelems; int /*<<< orphan*/  cta_index; int /*<<< orphan*/  cta_contents; } ;
typedef  TYPE_4__ ctf_array_t ;
struct TYPE_16__ {int /*<<< orphan*/  ctr_nelems; int /*<<< orphan*/  ctr_index; int /*<<< orphan*/  ctr_contents; } ;
typedef  TYPE_5__ ctf_arinfo_t ;

/* Variables and functions */
 scalar_t__ CTF_INFO_KIND (int /*<<< orphan*/ ) ; 
 scalar_t__ CTF_K_ARRAY ; 
 int /*<<< orphan*/  bzero (TYPE_5__*,int) ; 
 TYPE_2__* ctf_lookup_by_id (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbt_get_ctt_size (int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static void
fbt_array_info(linker_ctf_t *lc, ctf_id_t type, ctf_arinfo_t *arp)
{
	const ctf_header_t *hp = (const ctf_header_t *) lc->ctftab;
	const ctf_type_t *tp;
	const ctf_array_t *ap;
	ssize_t increment;

	bzero(arp, sizeof(*arp));

	if ((tp = ctf_lookup_by_id(lc, type)) == NULL)
		return;

	if (CTF_INFO_KIND(tp->ctt_info) != CTF_K_ARRAY)
		return;

	(void) fbt_get_ctt_size(hp->cth_version, tp, NULL, &increment);

	ap = (const ctf_array_t *)((uintptr_t)tp + increment);
	arp->ctr_contents = ap->cta_contents;
	arp->ctr_index = ap->cta_index;
	arp->ctr_nelems = ap->cta_nelems;
}
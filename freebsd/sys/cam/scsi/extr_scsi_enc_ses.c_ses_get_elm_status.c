#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int elm_idx; int /*<<< orphan*/  cstat; } ;
typedef  TYPE_3__ encioc_elm_status_t ;
struct TYPE_8__ {TYPE_1__* elm_map; } ;
struct TYPE_10__ {TYPE_2__ enc_cache; } ;
typedef  TYPE_4__ enc_softc_t ;
struct TYPE_7__ {int /*<<< orphan*/  encstat; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ses_get_elm_status(enc_softc_t *enc, encioc_elm_status_t *elms, int slpflag)
{
	unsigned int i = elms->elm_idx;

	memcpy(elms->cstat, &enc->enc_cache.elm_map[i].encstat, 4);
	return (0);
}
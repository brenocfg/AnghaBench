#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ descr_len; int /*<<< orphan*/ * descr; } ;
typedef  TYPE_3__ ses_element_t ;
struct TYPE_11__ {scalar_t__ elm_desc_len; int /*<<< orphan*/  elm_desc_str; scalar_t__ elm_idx; } ;
typedef  TYPE_4__ encioc_elm_desc_t ;
struct TYPE_9__ {TYPE_1__* elm_map; } ;
struct TYPE_12__ {TYPE_2__ enc_cache; } ;
typedef  TYPE_5__ enc_softc_t ;
struct TYPE_8__ {TYPE_3__* elm_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ses_get_elm_desc(enc_softc_t *enc, encioc_elm_desc_t *elmd)
{
	int i = (int)elmd->elm_idx;
	ses_element_t *elmpriv;

	/* Assume caller has already checked obj_id validity */
	elmpriv = enc->enc_cache.elm_map[i].elm_private;
	/* object might not have a descriptor */
	if (elmpriv == NULL || elmpriv->descr == NULL) {
		elmd->elm_desc_len = 0;
		return (0);
	}
	if (elmd->elm_desc_len > elmpriv->descr_len)
		elmd->elm_desc_len = elmpriv->descr_len;
	copyout(elmpriv->descr, elmd->elm_desc_str, elmd->elm_desc_len);
	return (0);
}
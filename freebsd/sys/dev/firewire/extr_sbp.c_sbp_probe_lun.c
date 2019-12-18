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
struct sbp_dev {int /*<<< orphan*/  product; int /*<<< orphan*/  revision; int /*<<< orphan*/  vendor; TYPE_1__* target; } ;
struct fw_device {int /*<<< orphan*/  csrrom; } ;
struct csrreg {scalar_t__ val; } ;
struct crom_context {int dummy; } ;
struct TYPE_2__ {struct fw_device* fwdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSRKEY_FIRM_VER ; 
 int /*<<< orphan*/  CSRKEY_MODEL ; 
 int /*<<< orphan*/  CSRKEY_VENDOR ; 
 int /*<<< orphan*/  CSRKEY_VER ; 
 scalar_t__ CSRVAL_T10SBP2 ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crom_init_context (struct crom_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crom_next (struct crom_context*) ; 
 int /*<<< orphan*/  crom_parse_text (struct crom_context*,int /*<<< orphan*/ ,int) ; 
 struct csrreg* crom_search_key (struct crom_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,scalar_t__) ; 

__attribute__((used)) static void
sbp_probe_lun(struct sbp_dev *sdev)
{
	struct fw_device *fwdev;
	struct crom_context c, *cc = &c;
	struct csrreg *reg;

	bzero(sdev->vendor, sizeof(sdev->vendor));
	bzero(sdev->product, sizeof(sdev->product));

	fwdev = sdev->target->fwdev;
	crom_init_context(cc, fwdev->csrrom);
	/* get vendor string */
	crom_search_key(cc, CSRKEY_VENDOR);
	crom_next(cc);
	crom_parse_text(cc, sdev->vendor, sizeof(sdev->vendor));
	/* skip to the unit directory for SBP-2 */
	while ((reg = crom_search_key(cc, CSRKEY_VER)) != NULL) {
		if (reg->val == CSRVAL_T10SBP2)
			break;
		crom_next(cc);
	}
	/* get firmware revision */
	reg = crom_search_key(cc, CSRKEY_FIRM_VER);
	if (reg != NULL)
		snprintf(sdev->revision, sizeof(sdev->revision),
						"%06x", reg->val);
	/* get product string */
	crom_search_key(cc, CSRKEY_MODEL);
	crom_next(cc);
	crom_parse_text(cc, sdev->product, sizeof(sdev->product));
}
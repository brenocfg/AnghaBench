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
struct TYPE_6__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  tid; } ;
struct TYPE_5__ {int /*<<< orphan*/  op; int /*<<< orphan*/  id; } ;
struct acpi_q_rule {int val; TYPE_2__ y; TYPE_1__ x; } ;
struct TYPE_7__ {int /*<<< orphan*/  AslCompilerRevision; int /*<<< orphan*/  OemRevision; int /*<<< orphan*/  AslCompilerId; int /*<<< orphan*/  OemTableId; int /*<<< orphan*/  OemId; } ;
typedef  TYPE_3__ ACPI_TABLE_HEADER ;

/* Variables and functions */
#define  CREATOR 131 
#define  CREATOR_REV 130 
 int FALSE ; 
#define  OEM 129 
#define  OEM_REV 128 
 int TRUE ; 
 int /*<<< orphan*/  aq_revcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aq_match_header(ACPI_TABLE_HEADER *hdr, const struct acpi_q_rule *match)
{
    int result;

    result = FALSE;
    switch (match->val) {
    case OEM:
	if (aq_strcmp(hdr->OemId, match->x.id) &&
	    aq_strcmp(hdr->OemTableId, match->y.tid))
	    result = TRUE;
	break;
    case CREATOR:
	if (aq_strcmp(hdr->AslCompilerId, match->x.id))
	    result = TRUE;
	break;
    case OEM_REV:
	if (aq_revcmp(hdr->OemRevision, match->x.op, match->y.rev))
	    result = TRUE;
	break;
    case CREATOR_REV:
	if (aq_revcmp(hdr->AslCompilerRevision, match->x.op, match->y.rev))
	    result = TRUE;
	break;
    }

    return (result);
}
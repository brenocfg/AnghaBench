#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ct_log_entry_type_t ;
struct TYPE_3__ {int entry_type; int /*<<< orphan*/  validation_status; } ;
typedef  TYPE_1__ SCT ;

/* Variables and functions */
 int /*<<< orphan*/  CT_F_SCT_SET_LOG_ENTRY_TYPE ; 
#define  CT_LOG_ENTRY_TYPE_NOT_SET 130 
#define  CT_LOG_ENTRY_TYPE_PRECERT 129 
#define  CT_LOG_ENTRY_TYPE_X509 128 
 int /*<<< orphan*/  CT_R_UNSUPPORTED_ENTRY_TYPE ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCT_VALIDATION_STATUS_NOT_SET ; 

int SCT_set_log_entry_type(SCT *sct, ct_log_entry_type_t entry_type)
{
    sct->validation_status = SCT_VALIDATION_STATUS_NOT_SET;

    switch (entry_type) {
    case CT_LOG_ENTRY_TYPE_X509:
    case CT_LOG_ENTRY_TYPE_PRECERT:
        sct->entry_type = entry_type;
        return 1;
    case CT_LOG_ENTRY_TYPE_NOT_SET:
        break;
    }
    CTerr(CT_F_SCT_SET_LOG_ENTRY_TYPE, CT_R_UNSUPPORTED_ENTRY_TYPE);
    return 0;
}
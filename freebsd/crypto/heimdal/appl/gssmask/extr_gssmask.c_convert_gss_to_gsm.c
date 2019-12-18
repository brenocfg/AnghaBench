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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSMERR_AP_MODIFIED ; 
 int /*<<< orphan*/  GSMERR_CONTINUE_NEEDED ; 
 int /*<<< orphan*/  GSMERR_ERROR ; 
 int /*<<< orphan*/  GSMERR_INVALID_TOKEN ; 
 int /*<<< orphan*/  GSMERR_OK ; 
#define  GSS_S_BAD_MIC 130 
#define  GSS_S_CONTINUE_NEEDED 129 
#define  GSS_S_DEFECTIVE_TOKEN 128 

__attribute__((used)) static int32_t
convert_gss_to_gsm(OM_uint32 maj_stat)
{
    switch(maj_stat) {
    case 0:
	return GSMERR_OK;
    case GSS_S_CONTINUE_NEEDED:
	return GSMERR_CONTINUE_NEEDED;
    case GSS_S_DEFECTIVE_TOKEN:
        return GSMERR_INVALID_TOKEN;
    case GSS_S_BAD_MIC:
	return GSMERR_AP_MODIFIED;
    default:
	return GSMERR_ERROR;
    }
}
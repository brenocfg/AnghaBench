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
typedef  int u8 ;
struct pseries_mc_errorlog {int error_type; int sub_err_type; } ;

/* Variables and functions */
#define  MC_ERROR_TYPE_ERAT 131 
#define  MC_ERROR_TYPE_SLB 130 
#define  MC_ERROR_TYPE_TLB 129 
#define  MC_ERROR_TYPE_UE 128 

__attribute__((used)) static inline u8 rtas_mc_error_sub_type(const struct pseries_mc_errorlog *mlog)
{
	switch (mlog->error_type) {
	case	MC_ERROR_TYPE_UE:
		return (mlog->sub_err_type & 0x07);
	case	MC_ERROR_TYPE_SLB:
	case	MC_ERROR_TYPE_ERAT:
	case	MC_ERROR_TYPE_TLB:
		return (mlog->sub_err_type & 0x03);
	default:
		return 0;
	}
}
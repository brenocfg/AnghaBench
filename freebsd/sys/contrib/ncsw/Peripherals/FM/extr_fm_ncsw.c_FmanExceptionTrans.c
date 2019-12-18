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
typedef  enum fman_exceptions { ____Placeholder_fman_exceptions } fman_exceptions ;
typedef  int e_FmExceptions ;

/* Variables and functions */
 int E_FMAN_EX_BMI_DISPATCH_RAM_ECC ; 
 int E_FMAN_EX_BMI_LIST_RAM_ECC ; 
 int E_FMAN_EX_BMI_STATISTICS_RAM_ECC ; 
 int E_FMAN_EX_BMI_STORAGE_PROFILE_ECC ; 
 int E_FMAN_EX_DMA_BUS_ERROR ; 
 int E_FMAN_EX_DMA_FM_WRITE_ECC ; 
 int E_FMAN_EX_DMA_READ_ECC ; 
 int E_FMAN_EX_DMA_SYSTEM_WRITE_ECC ; 
 int E_FMAN_EX_FPM_DOUBLE_ECC ; 
 int E_FMAN_EX_FPM_SINGLE_ECC ; 
 int E_FMAN_EX_FPM_STALL_ON_TASKS ; 
 int E_FMAN_EX_IRAM_ECC ; 
 int E_FMAN_EX_MURAM_ECC ; 
 int E_FMAN_EX_QMI_DEQ_FROM_UNKNOWN_PORTID ; 
 int E_FMAN_EX_QMI_DOUBLE_ECC ; 
 int E_FMAN_EX_QMI_SINGLE_ECC ; 
#define  e_FM_EX_BMI_DISPATCH_RAM_ECC 143 
#define  e_FM_EX_BMI_LIST_RAM_ECC 142 
#define  e_FM_EX_BMI_STATISTICS_RAM_ECC 141 
#define  e_FM_EX_BMI_STORAGE_PROFILE_ECC 140 
#define  e_FM_EX_DMA_BUS_ERROR 139 
#define  e_FM_EX_DMA_FM_WRITE_ECC 138 
#define  e_FM_EX_DMA_READ_ECC 137 
#define  e_FM_EX_DMA_SYSTEM_WRITE_ECC 136 
#define  e_FM_EX_FPM_DOUBLE_ECC 135 
#define  e_FM_EX_FPM_SINGLE_ECC 134 
#define  e_FM_EX_FPM_STALL_ON_TASKS 133 
#define  e_FM_EX_IRAM_ECC 132 
#define  e_FM_EX_MURAM_ECC 131 
#define  e_FM_EX_QMI_DEQ_FROM_UNKNOWN_PORTID 130 
#define  e_FM_EX_QMI_DOUBLE_ECC 129 
#define  e_FM_EX_QMI_SINGLE_ECC 128 

__attribute__((used)) static __inline__ enum fman_exceptions FmanExceptionTrans(e_FmExceptions exception)
{
    switch (exception) {
            case  e_FM_EX_DMA_BUS_ERROR:
                return E_FMAN_EX_DMA_BUS_ERROR;
            case  e_FM_EX_DMA_READ_ECC:
                return E_FMAN_EX_DMA_READ_ECC;
            case  e_FM_EX_DMA_SYSTEM_WRITE_ECC:
                return E_FMAN_EX_DMA_SYSTEM_WRITE_ECC;
            case  e_FM_EX_DMA_FM_WRITE_ECC:
                return E_FMAN_EX_DMA_FM_WRITE_ECC;
            case  e_FM_EX_FPM_STALL_ON_TASKS:
                return E_FMAN_EX_FPM_STALL_ON_TASKS;
            case  e_FM_EX_FPM_SINGLE_ECC:
                return E_FMAN_EX_FPM_SINGLE_ECC;
            case  e_FM_EX_FPM_DOUBLE_ECC:
                return E_FMAN_EX_FPM_DOUBLE_ECC;
            case  e_FM_EX_QMI_SINGLE_ECC:
                return E_FMAN_EX_QMI_SINGLE_ECC;
            case  e_FM_EX_QMI_DOUBLE_ECC:
                return E_FMAN_EX_QMI_DOUBLE_ECC;
            case  e_FM_EX_QMI_DEQ_FROM_UNKNOWN_PORTID:
                return E_FMAN_EX_QMI_DEQ_FROM_UNKNOWN_PORTID;
            case  e_FM_EX_BMI_LIST_RAM_ECC:
                return E_FMAN_EX_BMI_LIST_RAM_ECC;
            case  e_FM_EX_BMI_STORAGE_PROFILE_ECC:
                return E_FMAN_EX_BMI_STORAGE_PROFILE_ECC;
            case  e_FM_EX_BMI_STATISTICS_RAM_ECC:
                return E_FMAN_EX_BMI_STATISTICS_RAM_ECC;
            case  e_FM_EX_BMI_DISPATCH_RAM_ECC:
                return E_FMAN_EX_BMI_DISPATCH_RAM_ECC;
            case  e_FM_EX_IRAM_ECC:
                return E_FMAN_EX_IRAM_ECC;
            case  e_FM_EX_MURAM_ECC:
                return E_FMAN_EX_MURAM_ECC;
            default:
                return E_FMAN_EX_DMA_BUS_ERROR;
        }
}
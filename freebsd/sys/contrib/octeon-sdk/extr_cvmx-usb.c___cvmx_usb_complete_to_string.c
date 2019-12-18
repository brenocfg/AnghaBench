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
typedef  int cvmx_usb_complete_t ;

/* Variables and functions */
#define  CVMX_USB_COMPLETE_BABBLEERR 136 
#define  CVMX_USB_COMPLETE_CANCEL 135 
#define  CVMX_USB_COMPLETE_DATATGLERR 134 
#define  CVMX_USB_COMPLETE_ERROR 133 
#define  CVMX_USB_COMPLETE_FRAMEERR 132 
#define  CVMX_USB_COMPLETE_SHORT 131 
#define  CVMX_USB_COMPLETE_STALL 130 
#define  CVMX_USB_COMPLETE_SUCCESS 129 
#define  CVMX_USB_COMPLETE_XACTERR 128 

__attribute__((used)) static const char *__cvmx_usb_complete_to_string(cvmx_usb_complete_t complete_code)
{
    switch (complete_code)
    {
        case CVMX_USB_COMPLETE_SUCCESS: return "SUCCESS";
        case CVMX_USB_COMPLETE_SHORT:   return "SHORT";
        case CVMX_USB_COMPLETE_CANCEL:  return "CANCEL";
        case CVMX_USB_COMPLETE_ERROR:   return "ERROR";
        case CVMX_USB_COMPLETE_STALL:   return "STALL";
        case CVMX_USB_COMPLETE_XACTERR: return "XACTERR";
        case CVMX_USB_COMPLETE_DATATGLERR: return "DATATGLERR";
        case CVMX_USB_COMPLETE_BABBLEERR: return "BABBLEERR";
        case CVMX_USB_COMPLETE_FRAMEERR: return "FRAMEERR";
    }
    return "Update __cvmx_usb_complete_to_string";
}
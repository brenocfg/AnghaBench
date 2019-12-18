#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct flash_file_hdr {char* build; int asic_type_rev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__* POCE_SOFTC ;

/* Variables and functions */
 scalar_t__ IS_BE2 (TYPE_1__*) ; 
 scalar_t__ IS_BE3 (TYPE_1__*) ; 
 scalar_t__ IS_SH (TYPE_1__*) ; 
 int UFI_TYPE2 ; 
 int UFI_TYPE3 ; 
 int UFI_TYPE3R ; 
 int UFI_TYPE4 ; 
 int UFI_TYPE4R ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int oce_get_ufi_type(POCE_SOFTC sc,
                           const struct flash_file_hdr *fhdr)
{
        if (fhdr == NULL)
                goto be_get_ufi_exit;

        if (IS_SH(sc) && fhdr->build[0] == '4') {
                if (fhdr->asic_type_rev >= 0x10)
                        return UFI_TYPE4R;
                else
                        return UFI_TYPE4;
        } else if (IS_BE3(sc) && fhdr->build[0] == '3') {
                if (fhdr->asic_type_rev == 0x10)
                        return UFI_TYPE3R;
                else
                        return UFI_TYPE3;
        } else if (IS_BE2(sc) && fhdr->build[0] == '2')
                return UFI_TYPE2;

be_get_ufi_exit:
        device_printf(sc->dev,
                "UFI and Interface are not compatible for flashing\n");
        return -1;
}
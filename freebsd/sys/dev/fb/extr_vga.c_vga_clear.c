#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int vi_mem_model; } ;
struct TYPE_8__ {TYPE_1__ va_info; } ;
typedef  TYPE_2__ video_adapter_t ;

/* Variables and functions */
#define  V_INFO_MM_DIRECT 131 
#define  V_INFO_MM_PACKED 130 
#define  V_INFO_MM_PLANAR 129 
#define  V_INFO_MM_TEXT 128 
 int /*<<< orphan*/  direct_fill (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packed_fill (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  planar_fill (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vga_clear(video_adapter_t *adp)
{
    switch (adp->va_info.vi_mem_model) {
    case V_INFO_MM_TEXT:
	/* do nothing? XXX */
	break;
    case V_INFO_MM_PLANAR:
	planar_fill(adp, 0);
	break;
    case V_INFO_MM_PACKED:
	packed_fill(adp, 0);
	break;
    case V_INFO_MM_DIRECT:
	direct_fill(adp, 0);
	break;
    }
    return 0;
}
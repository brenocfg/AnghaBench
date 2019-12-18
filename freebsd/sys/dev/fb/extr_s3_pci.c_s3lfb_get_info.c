#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vi_flags; int /*<<< orphan*/  vi_buffer; } ;
typedef  TYPE_1__ video_info_t ;
typedef  int /*<<< orphan*/  video_adapter_t ;
struct s3pci_softc {int /*<<< orphan*/  mem_base; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int (* get_info ) (int /*<<< orphan*/ *,int,TYPE_1__*) ;} ;

/* Variables and functions */
 int M_VESA_BASE ; 
 int V_INFO_GRAPHICS ; 
 int V_INFO_LINEAR ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_4__* prevvidsw ; 
 int /*<<< orphan*/  s3pci_dev ; 
 int stub1 (int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static int
s3lfb_get_info(video_adapter_t *adp, int mode, video_info_t *info)
{
#if 0
	device_t dev = s3pci_dev;			/* XXX */
	struct s3pci_softc *sc = (struct s3pci_softc *)device_get_softc(dev);
#endif
	int error;

	if ((error = (*prevvidsw->get_info)(adp, mode, info)))
		return error;

#if 0
	/* Don't use linear addressing with text modes
	 */
	if ((mode > M_VESA_BASE) &&
		(info->vi_flags & V_INFO_GRAPHICS) &&
		!(info->vi_flags & V_INFO_LINEAR)) {

		info->vi_flags |= V_INFO_LINEAR;
		info->vi_buffer = sc->mem_base;

	} else {
		info->vi_buffer = 0;
	}
#endif

	return 0;
}
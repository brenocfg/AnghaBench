#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int vi_flags; int vi_buffer_size; int vi_planes; int /*<<< orphan*/  vi_buffer; } ;
struct TYPE_7__ {int va_buffer_size; int va_window_size; int va_window_gran; TYPE_1__ va_info; int /*<<< orphan*/  va_buffer; int /*<<< orphan*/  va_window; } ;
typedef  TYPE_2__ video_adapter_t ;
struct s3pci_softc {int /*<<< orphan*/  mem_base; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {int (* set_mode ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int ENXIO ; 
 int M_VESA_BASE ; 
 int /*<<< orphan*/  S3_CRTC_ADDR ; 
 int /*<<< orphan*/  S3_CRTC_VALUE ; 
 int V_INFO_GRAPHICS ; 
 int V_INFO_LINEAR ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int inb_enh (int /*<<< orphan*/ ) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_enh (int,int) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 TYPE_5__* prevvidsw ; 
 int /*<<< orphan*/  s3lfb_map_buffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s3pci_dev ; 
 int stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static int
s3lfb_set_mode(video_adapter_t *adp, int mode)
{
	device_t dev = s3pci_dev;			/* XXX */
	struct s3pci_softc *sc = (struct s3pci_softc *)device_get_softc(dev);
#if 0
	unsigned char tmp;
#endif
	int error;

	/* First, set the mode as if it was a classic VESA card
	 */
	if ((error = (*prevvidsw->set_mode)(adp, mode)))
		return error;

	/* If not in a linear mode (according to s3lfb_get_info() called
	 * by vesa_set_mode in the (*vidsw[adp->va_index]->get_info)...
	 * sequence, return with no error
	 */
#if 0
	if (!(adp->va_info.vi_flags & V_INFO_LINEAR))
		return 0;
#endif

	if ((mode <= M_VESA_BASE) ||
		!(adp->va_info.vi_flags & V_INFO_GRAPHICS) ||
		(adp->va_info.vi_flags & V_INFO_LINEAR))
		return 0;

	/* Ok, now apply the configuration to the card */

	outb_p(0x38, S3_CRTC_ADDR); outb_p(0x48, S3_CRTC_VALUE);
	outb_p(0x39, S3_CRTC_ADDR); outb_p(0xa5, S3_CRTC_VALUE);
       
       /* check that CR47 is read/write */
       
#if 0
	outb_p(0x47, S3_CRTC_ADDR); outb_p(0xff, S3_CRTC_VALUE);
	tmp = inb_p(S3_CRTC_VALUE);
	outb_p(0x00, S3_CRTC_VALUE);
	if ((tmp != 0xff) || (inb_p(S3_CRTC_VALUE)))
	{
		/* lock S3 registers */

		outb_p(0x39, S3_CRTC_ADDR); outb_p(0x5a, S3_CRTC_VALUE);
		outb_p(0x38, S3_CRTC_ADDR); outb_p(0x00, S3_CRTC_VALUE);

		return ENXIO;
	}
#endif

	/* enable enhanced register access */

	outb_p(0x40, S3_CRTC_ADDR);
	outb_p(inb_p(S3_CRTC_VALUE) | 1, S3_CRTC_VALUE);

	/* enable enhanced functions */

	outb_enh(inb_enh(0) | 1, 0x0);

	/* enable enhanced mode memory mapping */

	outb_p(0x31, S3_CRTC_ADDR);
	outb_p(inb_p(S3_CRTC_VALUE) | 8, S3_CRTC_VALUE);

	/* enable linear frame buffer and set address window to max */

	outb_p(0x58, S3_CRTC_ADDR);
	outb_p(inb_p(S3_CRTC_VALUE) | 0x13, S3_CRTC_VALUE);

	/* disabled enhanced register access */

	outb_p(0x40, S3_CRTC_ADDR);
	outb_p(inb_p(S3_CRTC_VALUE) & ~1, S3_CRTC_VALUE);

	/* lock S3 registers */

	outb_p(0x39, S3_CRTC_ADDR); outb_p(0x5a, S3_CRTC_VALUE);
	outb_p(0x38, S3_CRTC_ADDR); outb_p(0x00, S3_CRTC_VALUE);

	adp->va_info.vi_flags |= V_INFO_LINEAR;
	adp->va_info.vi_buffer = sc->mem_base;
	adp->va_buffer = s3lfb_map_buffer(adp->va_info.vi_buffer,
				adp->va_info.vi_buffer_size);
	adp->va_buffer_size = adp->va_info.vi_buffer_size;
	adp->va_window = adp->va_buffer;
	adp->va_window_size = adp->va_info.vi_buffer_size/adp->va_info.vi_planes;
	adp->va_window_gran = adp->va_info.vi_buffer_size/adp->va_info.vi_planes;

	return 0;
}
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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct video_adapter_softc {int width; int height; int stride; int fb_size; intptr_t fb_addr; intptr_t fb_paddr; int bpp; int depth; } ;
struct ipu3sc_softc {int pbase; scalar_t__ vbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPMEM_OFFSET (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  IMX_IPU_DP1 ; 
 int IPUV3_READ (struct ipu3sc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPUV3_WRITE (struct ipu3sc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpmem ; 
 int /*<<< orphan*/  ipu3_fb_malloc (struct ipu3sc_softc*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 struct video_adapter_softc va_softc ; 

__attribute__((used)) static void
ipu3_fb_init(void *arg)
{
	struct ipu3sc_softc *sc = arg;
	struct video_adapter_softc *va_sc = &va_softc;
	uint64_t w0sh96;
	uint32_t w1sh96;

	/* FW W0[137:125] - 96 = [41:29] */
	/* FH W0[149:138] - 96 = [53:42] */
	w0sh96 = IPUV3_READ(sc, cpmem, CPMEM_OFFSET(IMX_IPU_DP1, 23, 0, 16));
	w0sh96 <<= 32;
	w0sh96 |= IPUV3_READ(sc, cpmem, CPMEM_OFFSET(IMX_IPU_DP1, 23, 0, 12));

	va_sc->width = ((w0sh96 >> 29) & 0x1fff) + 1;
	va_sc->height = ((w0sh96 >> 42) & 0x0fff) + 1;

	/* SLY W1[115:102] - 96 = [19:6] */
	w1sh96 = IPUV3_READ(sc, cpmem, CPMEM_OFFSET(IMX_IPU_DP1, 23, 1, 12));
	va_sc->stride = ((w1sh96 >> 6) & 0x3fff) + 1;

	printf("%dx%d [%d]\n", va_sc->width, va_sc->height, va_sc->stride);
	va_sc->fb_size = va_sc->height * va_sc->stride;

	ipu3_fb_malloc(sc, va_sc->fb_size);

	/* DP1 + config_ch_23 + word_2 */
	IPUV3_WRITE(sc, cpmem, CPMEM_OFFSET(IMX_IPU_DP1, 23, 1, 0),
	    ((sc->pbase >> 3) | ((sc->pbase >> 3) << 29)) & 0xffffffff);

	IPUV3_WRITE(sc, cpmem, CPMEM_OFFSET(IMX_IPU_DP1, 23, 1, 4),
	    ((sc->pbase >> 3) >> 3) & 0xffffffff);

	va_sc->fb_addr = (intptr_t)sc->vbase;
	va_sc->fb_paddr = (intptr_t)sc->pbase;
	va_sc->bpp = va_sc->stride / va_sc->width;
	va_sc->depth = va_sc->bpp * 8;
}
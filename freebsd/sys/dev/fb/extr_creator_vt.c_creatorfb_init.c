#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  width ;
typedef  char uint32_t ;
typedef  int /*<<< orphan*/  type ;
struct vt_device {struct creatorfb_softc* vd_softc; } ;
struct TYPE_2__ {char fb_height; char fb_width; int fb_bpp; int fb_depth; int fb_stride; int fb_size; int fb_cmsize; int /*<<< orphan*/  fb_cmap; int /*<<< orphan*/  fb_pbase; } ;
struct creatorfb_softc {TYPE_1__ fb; int /*<<< orphan*/ * memt; int /*<<< orphan*/  memh; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  name ;
typedef  char ihandle_t ;
typedef  int /*<<< orphan*/  height ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int CN_DEAD ; 
 int CN_INTERNAL ; 
 int /*<<< orphan*/  COLOR_FORMAT_RGB ; 
 int /*<<< orphan*/  FFB_DFB24 ; 
 scalar_t__ OF_decode_addr (int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_getprop (int,char*,char*,int) ; 
 int OF_getproplen (int,char*) ; 
 int OF_instance_to_package (char) ; 
 char OF_open (char*) ; 
 struct creatorfb_softc creatorfb_conssoftc ; 
 int /*<<< orphan*/  sparc64_fake_bustag (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  vt_fb_init (struct vt_device*) ; 
 int /*<<< orphan*/  vt_generate_cons_palette (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int
creatorfb_init(struct vt_device *vd)
{
	struct creatorfb_softc *sc;
	phandle_t chosen;
	phandle_t node;
	ihandle_t handle;
	uint32_t height, width;
	char type[64], name[64];
	bus_addr_t phys;
	int space;

	/* Initialize softc */
	vd->vd_softc = sc = &creatorfb_conssoftc;

	chosen = OF_finddevice("/chosen");
	OF_getprop(chosen, "stdout", &handle, sizeof(ihandle_t));
	node = OF_instance_to_package(handle);
	if (node == -1) {
		/*
		 * The "/chosen/stdout" does not exist try
		 * using "screen" directly.
		 */
		node = OF_finddevice("screen");
		handle = OF_open("screen");
	}
	OF_getprop(node, "device_type", type, sizeof(type));
	if (strcmp(type, "display") != 0)
		return (CN_DEAD);

	OF_getprop(node, "name", name, sizeof(name));
	if (strcmp(name, "SUNW,ffb") != 0 && strcmp(name, "SUNW,afb") != 0)
		return (CN_DEAD);

	/* Make sure we have needed properties */
	if (OF_getproplen(node, "height") != sizeof(height) ||
	    OF_getproplen(node, "width") != sizeof(width))
		return (CN_DEAD);

	OF_getprop(node, "height", &height, sizeof(height));
	OF_getprop(node, "width", &width, sizeof(width));

	sc->fb.fb_height = height;
	sc->fb.fb_width = width;
	sc->fb.fb_bpp = sc->fb.fb_depth = 32;
	sc->fb.fb_stride = 8192; /* Fixed */
	sc->fb.fb_size = sc->fb.fb_height * sc->fb.fb_stride;

	/* Map linear framebuffer */
	if (OF_decode_addr(node, FFB_DFB24, &space, &phys) != 0)
		return (CN_DEAD);
	sc->fb.fb_pbase = phys;
	sc->memh = sparc64_fake_bustag(space, phys, &sc->memt[0]);

	/* 32-bit VGA palette */
	vt_generate_cons_palette(sc->fb.fb_cmap, COLOR_FORMAT_RGB,
	    255, 0, 255, 8, 255, 16);
	sc->fb.fb_cmsize = 16;

	vt_fb_init(vd);

	return (CN_INTERNAL);
}
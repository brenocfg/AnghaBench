#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vi_width; int vi_height; int vi_depth; int vi_planes; } ;
typedef  TYPE_1__ video_info_t ;
typedef  int /*<<< orphan*/  video_adapter_t ;
struct TYPE_7__ {scalar_t__ data_size; int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {int width; int height; int bpp; int planes; } ;

/* Variables and functions */
 int ENODEV ; 
#define  M_VESA_CG1024x768 131 
#define  M_VESA_CG640x480 130 
#define  M_VESA_CG800x600 129 
#define  M_VGA_CG320 128 
 scalar_t__ bootverbose ; 
 TYPE_4__ pcx_decoder ; 
 TYPE_3__ pcx_info ; 
 scalar_t__ pcx_init (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int splash_mode ; 
 scalar_t__ vidd_get_info (int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static int
pcx_start(video_adapter_t *adp)
{
	static int modes[] = {
		M_VGA_CG320,
		M_VESA_CG640x480,
		M_VESA_CG800x600,
		M_VESA_CG1024x768,
		-1,
	};
	video_info_t info;
	int i;

	if (pcx_decoder.data == NULL ||
	    pcx_decoder.data_size <= 0 ||
	    pcx_init(pcx_decoder.data, pcx_decoder.data_size))
		return (ENODEV);

	if (bootverbose)
		printf("splash_pcx: image good:\n"
		    "  width = %d\n"
		    "  height = %d\n"
		    "  depth = %d\n"
		    "  planes = %d\n",
		    pcx_info.width, pcx_info.height,
		    pcx_info.bpp, pcx_info.planes);

	for (i = 0; modes[i] >= 0; ++i) {
		if (vidd_get_info(adp, modes[i], &info) != 0)
			continue;
		if (bootverbose)
			printf("splash_pcx: considering mode %d:\n"
			    "  vi_width = %d\n"
			    "  vi_height = %d\n"
			    "  vi_depth = %d\n"
			    "  vi_planes = %d\n",
			    modes[i],
			    info.vi_width, info.vi_height,
			    info.vi_depth, info.vi_planes);
		if (info.vi_width >= pcx_info.width
		    && info.vi_height >= pcx_info.height
		    && info.vi_depth == pcx_info.bpp
		    && info.vi_planes == pcx_info.planes)
			break;
	}

	splash_mode = modes[i];
	if (splash_mode == -1)
		return (ENODEV);
	if (bootverbose)
		printf("splash_pcx: selecting mode %d\n", splash_mode);
	return (0);
}
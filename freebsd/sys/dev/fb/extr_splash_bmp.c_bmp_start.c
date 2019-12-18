#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  vi_depth; int /*<<< orphan*/  vi_height; int /*<<< orphan*/  vi_width; } ;
typedef  TYPE_1__ video_info_t ;
typedef  int /*<<< orphan*/  video_adapter_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {scalar_t__ data_size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ENODEV ; 
#define  M_CG640x480 132 
#define  M_VESA_CG1024x768 131 
#define  M_VESA_CG640x480 130 
#define  M_VESA_CG800x600 129 
#define  M_VGA_CG320 128 
 scalar_t__ bmp_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ bmp_decoder ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int splash_mode ; 
 scalar_t__ vidd_get_info (int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static int 
bmp_start(video_adapter_t *adp)
{
    /* currently only 256-color modes are supported XXX */
    static int		modes[] = {
			M_VESA_CG640x480,
			M_VESA_CG800x600,
			M_VESA_CG1024x768,
			M_CG640x480,
    			/*
			 * As 320x200 doesn't generally look great,
			 * it's least preferred here.
			 */
			M_VGA_CG320,
			-1,
    };
    video_info_t 	info;
    int			i;

    if ((bmp_decoder.data == NULL) || (bmp_decoder.data_size <= 0)) {
	printf("splash_bmp: No bitmap file found\n");
	return ENODEV;
    }
    for (i = 0; modes[i] >= 0; ++i) {
	if ((vidd_get_info(adp, modes[i], &info) == 0) && 
	    (bmp_Init((u_char *)bmp_decoder.data, info.vi_width,
		      info.vi_height, info.vi_depth) == 0))
	    break;
    }
    splash_mode = modes[i];
    if (splash_mode < 0)
	printf("splash_bmp: No appropriate video mode found\n");
    if (bootverbose)
	printf("bmp_start(): splash_mode:%d\n", splash_mode);
    return ((splash_mode < 0) ? ENODEV : 0);
}
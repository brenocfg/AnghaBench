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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int u_int ;
struct efi_fb {int fb_width; int fb_height; int fb_stride; int fb_mask_red; int fb_mask_green; int fb_mask_blue; scalar_t__ fb_size; scalar_t__ fb_addr; } ;

/* Variables and functions */
 int efifb_color_depth (struct efi_fb*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
print_efifb(int mode, struct efi_fb *efifb, int verbose)
{
	u_int depth;

	if (mode >= 0)
		printf("mode %d: ", mode);
	depth = efifb_color_depth(efifb);
	printf("%ux%ux%u, stride=%u", efifb->fb_width, efifb->fb_height,
	    depth, efifb->fb_stride);
	if (verbose) {
		printf("\n    frame buffer: address=%jx, size=%jx",
		    (uintmax_t)efifb->fb_addr, (uintmax_t)efifb->fb_size);
		printf("\n    color mask: R=%08x, G=%08x, B=%08x\n",
		    efifb->fb_mask_red, efifb->fb_mask_green,
		    efifb->fb_mask_blue);
	}
}
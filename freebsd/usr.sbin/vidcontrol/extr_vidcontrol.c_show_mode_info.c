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
struct video_info {int vi_mode; scalar_t__ vi_width; scalar_t__ vi_height; scalar_t__ vi_cwidth; scalar_t__ vi_cheight; int vi_flags; int vi_mem_model; int vi_depth; int vi_planes; int vi_buffer; scalar_t__ vi_buffer_size; scalar_t__ vi_window_gran; scalar_t__ vi_window_size; int /*<<< orphan*/  vi_window; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CONS_MODEINFO ; 
 int M_VESA_MODE_MAX ; 
 int V_INFO_GRAPHICS ; 
#define  V_INFO_MM_CGA 132 
#define  V_INFO_MM_DIRECT 131 
#define  V_INFO_MM_HGC 130 
#define  V_INFO_MM_PACKED 129 
 int V_INFO_MM_PLANAR ; 
#define  V_INFO_MM_VGAX 128 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct video_info*) ; 
 int /*<<< orphan*/  memset (struct video_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__,scalar_t__,...) ; 

__attribute__((used)) static void
show_mode_info(void)
{
	char buf[80];
	struct video_info info;
	int c;
	int mm;
	int mode;

	printf("    mode#     flags   type    size       "
	       "font      window      linear buffer\n");
	printf("---------------------------------------"
	       "---------------------------------------\n");

	memset(&info, 0, sizeof(info));
	for (mode = 0; mode <= M_VESA_MODE_MAX; ++mode) {
		info.vi_mode = mode;
		if (ioctl(0, CONS_MODEINFO, &info))
			continue;
		if (info.vi_mode != mode)
			continue;
		if (info.vi_width == 0 && info.vi_height == 0 &&
		    info.vi_cwidth == 0 && info.vi_cheight == 0)
			continue;

		printf("%3d (0x%03x)", mode, mode);
    		printf(" 0x%08x", info.vi_flags);
		if (info.vi_flags & V_INFO_GRAPHICS) {
			c = 'G';

			if (info.vi_mem_model == V_INFO_MM_PLANAR)
				snprintf(buf, sizeof(buf), "%dx%dx%d %d",
				    info.vi_width, info.vi_height, 
				    info.vi_depth, info.vi_planes);
			else {
				switch (info.vi_mem_model) {
				case V_INFO_MM_PACKED:
					mm = 'P';
					break;
				case V_INFO_MM_DIRECT:
					mm = 'D';
					break;
				case V_INFO_MM_CGA:
					mm = 'C';
					break;
				case V_INFO_MM_HGC:
					mm = 'H';
					break;
				case V_INFO_MM_VGAX:
					mm = 'V';
					break;
				default:
					mm = ' ';
					break;
				}
				snprintf(buf, sizeof(buf), "%dx%dx%d %c",
				    info.vi_width, info.vi_height, 
				    info.vi_depth, mm);
			}
		} else {
			c = 'T';

			snprintf(buf, sizeof(buf), "%dx%d",
				 info.vi_width, info.vi_height);
		}

		printf(" %c %-15s", c, buf);
		snprintf(buf, sizeof(buf), "%dx%d", 
			 info.vi_cwidth, info.vi_cheight); 
		printf(" %-5s", buf);
    		printf(" 0x%05zx %2dk %2dk", 
		       info.vi_window, (int)info.vi_window_size/1024, 
		       (int)info.vi_window_gran/1024);
    		printf(" 0x%08zx %dk\n",
		       info.vi_buffer, (int)info.vi_buffer_size/1024);
	}
}
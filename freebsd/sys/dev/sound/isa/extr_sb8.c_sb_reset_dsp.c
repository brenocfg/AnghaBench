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
struct sb_info {int /*<<< orphan*/  io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  SBDSP_RST ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 
 int sb_get_byte (struct sb_info*) ; 
 int /*<<< orphan*/  sb_wr (struct sb_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sb_reset_dsp(struct sb_info *sb)
{
    	sb_wr(sb, SBDSP_RST, 3);
    	DELAY(100);
    	sb_wr(sb, SBDSP_RST, 0);
    	if (sb_get_byte(sb) != 0xAA) {
        	DEB(printf("sb_reset_dsp 0x%lx failed\n",
			   rman_get_start(sb->io_base)));
		return ENXIO;	/* Sorry */
    	}
    	return 0;
}
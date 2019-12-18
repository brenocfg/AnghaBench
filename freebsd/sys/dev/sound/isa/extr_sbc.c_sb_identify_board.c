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
struct resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_CMD_GETID ; 
 int /*<<< orphan*/  DSP_CMD_GETVER ; 
 int /*<<< orphan*/  sb_cmd (struct resource*,int /*<<< orphan*/ ) ; 
 int sb_get_byte (struct resource*) ; 

__attribute__((used)) static int
sb_identify_board(struct resource *io)
{
	int ver, essver, rev;

    	sb_cmd(io, DSP_CMD_GETVER);	/* Get version */
    	ver = (sb_get_byte(io) << 8) | sb_get_byte(io);
	if (ver < 0x100 || ver > 0x4ff) return 0;
    	if (ver == 0x0301) {
	    	/* Try to detect ESS chips. */
	    	sb_cmd(io, DSP_CMD_GETID); /* Return ident. bytes. */
	    	essver = (sb_get_byte(io) << 8) | sb_get_byte(io);
	    	rev = essver & 0x000f;
	    	essver &= 0xfff0;
	    	if (essver == 0x4880) ver |= 0x1000;
	    	else if (essver == 0x6880) ver = 0x0500 | rev;
	}
	return ver;
}
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
typedef  int u8 ;
struct vblk {int flags; int type; scalar_t__ obj_id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  VBLK_CMP3 134 
#define  VBLK_DGR3 133 
#define  VBLK_DGR4 132 
#define  VBLK_DSK3 131 
#define  VBLK_DSK4 130 
#define  VBLK_PRT3 129 
#define  VBLK_VOL5 128 
 int /*<<< orphan*/  ldm_debug (char*,unsigned long long,int) ; 
 int /*<<< orphan*/  ldm_error (char*,...) ; 
 scalar_t__ ldm_get_vnum (int const*) ; 
 int /*<<< orphan*/  ldm_get_vstr (int const*,int /*<<< orphan*/ ,int) ; 
 int ldm_parse_cmp3 (int const*,int,struct vblk*) ; 
 int ldm_parse_dgr3 (int const*,int,struct vblk*) ; 
 int ldm_parse_dgr4 (int const*,int,struct vblk*) ; 
 int ldm_parse_dsk3 (int const*,int,struct vblk*) ; 
 int ldm_parse_dsk4 (int const*,int,struct vblk*) ; 
 int ldm_parse_prt3 (int const*,int,struct vblk*) ; 
 int ldm_parse_vol5 (int const*,int,struct vblk*) ; 
 int ldm_relative (int const*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ldm_parse_vblk (const u8 *buf, int len, struct vblk *vb)
{
	bool result = false;
	int r_objid;

	BUG_ON (!buf || !vb);

	r_objid = ldm_relative (buf, len, 0x18, 0);
	if (r_objid < 0) {
		ldm_error ("VBLK header is corrupt.");
		return false;
	}

	vb->flags  = buf[0x12];
	vb->type   = buf[0x13];
	vb->obj_id = ldm_get_vnum (buf + 0x18);
	ldm_get_vstr (buf+0x18+r_objid, vb->name, sizeof (vb->name));

	switch (vb->type) {
		case VBLK_CMP3:  result = ldm_parse_cmp3 (buf, len, vb); break;
		case VBLK_DSK3:  result = ldm_parse_dsk3 (buf, len, vb); break;
		case VBLK_DSK4:  result = ldm_parse_dsk4 (buf, len, vb); break;
		case VBLK_DGR3:  result = ldm_parse_dgr3 (buf, len, vb); break;
		case VBLK_DGR4:  result = ldm_parse_dgr4 (buf, len, vb); break;
		case VBLK_PRT3:  result = ldm_parse_prt3 (buf, len, vb); break;
		case VBLK_VOL5:  result = ldm_parse_vol5 (buf, len, vb); break;
	}

	if (result)
		ldm_debug ("Parsed VBLK 0x%llx (type: 0x%02x) ok.",
			 (unsigned long long) vb->obj_id, vb->type);
	else
		ldm_error ("Failed to parse VBLK 0x%llx (type: 0x%02x).",
			(unsigned long long) vb->obj_id, vb->type);

	return result;
}
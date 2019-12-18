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
struct vt_font_map {unsigned int vfm_src; unsigned int vfm_dst; unsigned int vfm_len; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
vtfont_validate_map(struct vt_font_map *vfm, unsigned int length,
    unsigned int glyph_count)
{
	unsigned int i, last = 0;

	for (i = 0; i < length; i++) {
		/* Not ordered. */
		if (i > 0 && vfm[i].vfm_src <= last)
			return (EINVAL);
		/*
		 * Destination extends amount of glyphs.
		 */
		if (vfm[i].vfm_dst >= glyph_count ||
		    vfm[i].vfm_dst + vfm[i].vfm_len >= glyph_count)
			return (EINVAL);
		last = vfm[i].vfm_src + vfm[i].vfm_len;
	}

	return (0);
}
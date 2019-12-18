#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int width; int height; int glyph_count; int* map_count; int /*<<< orphan*/  glyphs; int /*<<< orphan*/ * map; } ;
typedef  TYPE_1__ vfnt_t ;
struct vt_font_map {int dummy; } ;
struct vt_font {size_t vf_height; int vf_width; int vf_refcount; int* vf_map_count; void* vf_bytes; void** vf_map; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  M_VTFONT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 unsigned int VFNT_MAPS ; 
 int VTFONT_MAXDIMENSION ; 
 int VTFONT_MAXGLYPHS ; 
 size_t VTFONT_MAXGLYPHSIZE ; 
 int VTFONT_MAXMAPPINGS ; 
 int copyin (int /*<<< orphan*/ ,void*,size_t) ; 
 size_t howmany (int,int) ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vtfont_unref (struct vt_font*) ; 
 int vtfont_validate_map (void*,int,size_t) ; 

int
vtfont_load(vfnt_t *f, struct vt_font **ret)
{
	size_t glyphsize, mapsize;
	struct vt_font *vf;
	int error;
	unsigned int i;

	/* Make sure the dimensions are valid. */
	if (f->width < 1 || f->height < 1)
		return (EINVAL);
	if (f->width > VTFONT_MAXDIMENSION || f->height > VTFONT_MAXDIMENSION ||
	    f->glyph_count > VTFONT_MAXGLYPHS)
		return (E2BIG);

	/* Not too many mappings. */
	for (i = 0; i < VFNT_MAPS; i++)
		if (f->map_count[i] > VTFONT_MAXMAPPINGS)
			return (E2BIG);

	/* Character 0 must always be present. */
	if (f->glyph_count < 1)
		return (EINVAL);

	glyphsize = howmany(f->width, 8) * f->height * f->glyph_count;
	if (glyphsize > VTFONT_MAXGLYPHSIZE)
		return (E2BIG);

	/* Allocate new font structure. */
	vf = malloc(sizeof *vf, M_VTFONT, M_WAITOK | M_ZERO);
	vf->vf_bytes = malloc(glyphsize, M_VTFONT, M_WAITOK);
	vf->vf_height = f->height;
	vf->vf_width = f->width;
	vf->vf_refcount = 1;

	/* Allocate, copy in, and validate mappings. */
	for (i = 0; i < VFNT_MAPS; i++) {
		vf->vf_map_count[i] = f->map_count[i];
		if (f->map_count[i] == 0)
			continue;
		mapsize = f->map_count[i] * sizeof(struct vt_font_map);
		vf->vf_map[i] = malloc(mapsize, M_VTFONT, M_WAITOK);
		error = copyin(f->map[i], vf->vf_map[i], mapsize);
		if (error)
			goto bad;
		error = vtfont_validate_map(vf->vf_map[i], vf->vf_map_count[i],
		    f->glyph_count);
		if (error)
			goto bad;
	}

	/* Copy in glyph data. */
	error = copyin(f->glyphs, vf->vf_bytes, glyphsize);
	if (error)
		goto bad;

	/* Success. */
	*ret = vf;
	return (0);

bad:	vtfont_unref(vf);
	return (error);
}
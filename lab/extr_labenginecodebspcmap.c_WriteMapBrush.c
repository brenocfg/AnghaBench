#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {float** p; } ;
typedef  TYPE_1__ winding_t ;
typedef  scalar_t__* vec3_t ;
struct TYPE_13__ {int flags; size_t planenum; size_t texinfo; int contents; } ;
typedef  TYPE_2__ side_t ;
typedef  int qboolean ;
struct TYPE_14__ {float dist; scalar_t__* normal; } ;
typedef  TYPE_3__ plane_t ;
struct TYPE_15__ {int contents; int brushnum; int numsides; TYPE_2__* original_sides; } ;
typedef  TYPE_4__ mapbrush_t ;
struct TYPE_16__ {float** vecs; char* texture; int flags; int value; } ;
typedef  TYPE_5__ map_texinfo_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* BaseWindingForPlane (scalar_t__*,float) ; 
 int CONTENTS_DUMMYFENCE ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_MIST ; 
 int CONTENTS_MONSTERCLIP ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_WATER ; 
 float DotProduct (scalar_t__*,scalar_t__*) ; 
 int FindFloatPlane (scalar_t__*,float) ; 
 int /*<<< orphan*/  FreeWinding (TYPE_1__*) ; 
 int /*<<< orphan*/  Log_Write (char*,int) ; 
 scalar_t__ MAPTYPE_QUAKE2 ; 
 scalar_t__ MAPTYPE_QUAKE3 ; 
 scalar_t__ MAPTYPE_SIN ; 
 int Q_PI ; 
 int SFL_BEVEL ; 
 size_t TEXINFO_NODE ; 
 int /*<<< orphan*/  TextureAxisFromPlane (TYPE_3__*,scalar_t__*,scalar_t__*) ; 
 int VectorNormalize2 (float*,scalar_t__*) ; 
 int atan2 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  c_writtenbrushes ; 
 double fabs (float) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ loadedmaptype ; 
 TYPE_5__* map_texinfo ; 
 TYPE_3__* mapplanes ; 
 scalar_t__ noliquids ; 

qboolean WriteMapBrush(FILE *fp, mapbrush_t *brush, vec3_t origin)
{
	int sn, rotate, shift[2], sv, tv, planenum, p1, i, j;
	float scale[2], originshift[2], ang1, ang2, newdist;
	vec3_t vecs[2], axis[2];
	map_texinfo_t *ti;
	winding_t *w;
	side_t *s;
	plane_t *plane;

	if (noliquids)
	{
		if (brush->contents & (CONTENTS_WATER|CONTENTS_SLIME|CONTENTS_LAVA))
		{
			return true;
		} //end if
	} //end if
	//if the brush has no contents
	if (!brush->contents) return true;
	//print the leading {
	if (fprintf(fp, " { //brush %d\n", brush->brushnum) < 0) return false;
	//write brush sides
	for (sn = 0; sn < brush->numsides; sn++)
	{
		s = brush->original_sides + sn;
		//don't write out bevels
		if (!(s->flags & SFL_BEVEL))
		{
			//if the entity has an origin set
			if (origin[0] || origin[1] || origin[2])
			{
				newdist = mapplanes[s->planenum].dist +
					DotProduct(mapplanes[s->planenum].normal, origin);
				planenum = FindFloatPlane(mapplanes[s->planenum].normal, newdist);
			} //end if
			else
			{
				planenum = s->planenum;
			} //end else
			//always take the first plane, then flip the points if necesary
			plane = &mapplanes[planenum & ~1];
			w = BaseWindingForPlane(plane->normal, plane->dist);
			//
			for (i = 0; i < 3; i++)
			{
				for (j = 0; j < 3; j++)
				{
					if (fabs(w->p[i][j]) < 0.2) w->p[i][j] = 0;
					else if (fabs((int)w->p[i][j] - w->p[i][j]) < 0.3) w->p[i][j] = (int) w->p[i][j];
					//w->p[i][j] = (int) (w->p[i][j] + 0.2);
				} //end for
			} //end for
			//three non-colinear points to define the plane
			if (planenum & 1) p1 = 1;
			else p1 = 0;
			if (fprintf(fp,"  ( %5i %5i %5i ) ", (int)w->p[p1][0], (int)w->p[p1][1], (int)w->p[p1][2]) < 0) return false;
			if (fprintf(fp,"( %5i %5i %5i ) ", (int)w->p[!p1][0], (int)w->p[!p1][1], (int)w->p[!p1][2]) < 0) return false;
			if (fprintf(fp,"( %5i %5i %5i ) ", (int)w->p[2][0], (int)w->p[2][1], (int)w->p[2][2]) < 0) return false;
			//free the winding
			FreeWinding(w);
			//
			if (s->texinfo == TEXINFO_NODE)
			{
				if (brush->contents & CONTENTS_PLAYERCLIP)
				{
					//player clip
					if (loadedmaptype == MAPTYPE_SIN)
					{
						if (fprintf(fp, "generic/misc/clip 0 0 0 1 1") < 0) return false;
					} //end if
					else if (loadedmaptype == MAPTYPE_QUAKE2)
					{	//FIXME: don't always use e1u1
						if (fprintf(fp, "e1u1/clip 0 0 0 1 1") < 0) return false;
					} //end else
					else if (loadedmaptype == MAPTYPE_QUAKE3)
					{
						if (fprintf(fp, "e1u1/clip 0 0 0 1 1") < 0) return false;
					} //end else if
					else
					{
						if (fprintf(fp, "clip 0 0 0 1 1") < 0) return false;
					} //end else
				} //end if
				else if (brush->contents == CONTENTS_MONSTERCLIP)
				{
					//monster clip
					if (loadedmaptype == MAPTYPE_SIN)
					{
						if (fprintf(fp, "generic/misc/monster 0 0 0 1 1") < 0) return false;
					} //end if
					else if (loadedmaptype == MAPTYPE_QUAKE2)
					{
						if (fprintf(fp, "e1u1/clip_mon 0 0 0 1 1") < 0) return false;
					} //end else
					else
					{
						if (fprintf(fp, "clip 0 0 0 1 1") < 0) return false;
					} //end else
				} //end else
				else
				{
					if (fprintf(fp, "clip 0 0 0 1 1") < 0) return false;
					Log_Write("brush->contents = %d\n", brush->contents);
				} //end else
			} //end if
			else if (loadedmaptype == MAPTYPE_SIN && s->texinfo == 0)
			{
				if (brush->contents & CONTENTS_DUMMYFENCE)
				{
					if (fprintf(fp, "generic/misc/fence 0 0 0 1 1") < 0) return false;
				} //end if
				else if (brush->contents & CONTENTS_MIST)
				{
					if (fprintf(fp, "generic/misc/volumetric_base 0 0 0 1 1") < 0) return false;
				} //end if
				else //unknown so far
				{
					if (fprintf(fp, "generic/misc/red 0 0 0 1 1") < 0) return false;
				} //end else
			} //end if
			else if (loadedmaptype == MAPTYPE_QUAKE3)
			{
				//always use the same texture
				if (fprintf(fp, "e2u3/floor1_2 0 0 0 1 1 1 0 0") < 0) return false;
			} //end else if
			else
			{
				//*
				ti = &map_texinfo[s->texinfo];
				//the scaling of the texture
				scale[0] = 1 / VectorNormalize2(ti->vecs[0], vecs[0]);
				scale[1] = 1 / VectorNormalize2(ti->vecs[1], vecs[1]);
				//
				TextureAxisFromPlane(plane, axis[0], axis[1]);
				//calculate texture shift done by entity origin
				originshift[0] = DotProduct(origin, axis[0]);
				originshift[1] = DotProduct(origin, axis[1]);
				//the texture shift without origin shift
				shift[0] = ti->vecs[0][3] - originshift[0];
				shift[1] = ti->vecs[1][3] - originshift[1];
				//
				if (axis[0][0]) sv = 0;
				else if (axis[0][1]) sv = 1;
				else sv = 2;
				if (axis[1][0]) tv = 0;
				else if (axis[1][1]) tv = 1;
				else tv = 2;
				//calculate rotation of texture
				if (vecs[0][tv] == 0) ang1 = vecs[0][sv] > 0 ? 90.0 : -90.0;
				else ang1 = atan2(vecs[0][sv], vecs[0][tv]) * 180 / Q_PI;
				if (ang1 < 0) ang1 += 360;
				if (ang1 >= 360) ang1 -= 360;
				if (axis[0][tv] == 0) ang2 = axis[0][sv] > 0 ? 90.0 : -90.0;
				else ang2 = atan2(axis[0][sv], axis[0][tv]) * 180 / Q_PI;
				if (ang2 < 0) ang2 += 360;
				if (ang2 >= 360) ang2 -= 360;
				rotate = ang2 - ang1;
				if (rotate < 0) rotate += 360;
				if (rotate >= 360) rotate -= 360;
				//write the texture info
				if (fprintf(fp, "%s %d %d %d", ti->texture, shift[0], shift[1], rotate) < 0) return false;
				if (fabs(scale[0] - ((int) scale[0])) < 0.001)
				{
					if (fprintf(fp, " %d", (int) scale[0]) < 0) return false;
				} //end if
				else
				{
					if (fprintf(fp, " %4f", scale[0]) < 0) return false;
				} //end if
				if (fabs(scale[1] - ((int) scale[1])) < 0.001)
				{
					if (fprintf(fp, " %d", (int) scale[1]) < 0) return false;
				} //end if
				else
				{
					if (fprintf(fp, " %4f", scale[1]) < 0) return false;
				} //end else
				//write the extra brush side info
				if (loadedmaptype == MAPTYPE_QUAKE2)
				{
					if (fprintf(fp, " %d %d %d", s->contents, ti->flags, ti->value) < 0) return false;
				} //end if
				//*/
			} //end else
			if (fprintf(fp, "\n") < 0) return false;
		} //end if
	} //end if
	if (fprintf(fp, " }\n") < 0) return false;
	c_writtenbrushes++;
	return true;
}
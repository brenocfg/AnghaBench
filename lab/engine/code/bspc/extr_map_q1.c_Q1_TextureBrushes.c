#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int vec_t ;
struct TYPE_16__ {int flags; int surf; int texinfo; int /*<<< orphan*/  winding; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_17__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ q1_miptex_t ;
struct TYPE_18__ {int* dataofs; } ;
typedef  TYPE_3__ q1_dmiptexlump_t ;
typedef  int /*<<< orphan*/  defaultvec ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_19__ {int numsides; struct TYPE_19__* next; TYPE_1__* sides; } ;
typedef  TYPE_4__ bspbrush_t ;
struct TYPE_23__ {int nexttexinfo; int /*<<< orphan*/  texture; scalar_t__ value; int /*<<< orphan*/  flags; int /*<<< orphan*/ ** vecs; } ;
struct TYPE_22__ {scalar_t__ planenum; int texinfo; } ;
struct TYPE_21__ {scalar_t__ planenum; } ;
struct TYPE_20__ {size_t miptex; int /*<<< orphan*/  flags; int /*<<< orphan*/ ** vecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBrush (TYPE_4__*) ; 
 int /*<<< orphan*/  Log_Write (char*,int) ; 
 float Q1_FaceOnWinding (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* Q1_SplitBrushWithFace (TYPE_4__*,TYPE_7__*) ; 
 int SFL_TEXTURED ; 
 int TEXINFO_NODE ; 
 double VectorLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lessbrushes ; 
 int map_numtexinfo ; 
 TYPE_8__* map_texinfo ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 TYPE_7__* q1_dfaces ; 
 TYPE_6__* q1_dnodes ; 
 scalar_t__ q1_dtexdata ; 
 int q1_numfaces ; 
 int q1_texdatasize ; 
 TYPE_5__* q1_texinfo ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bspbrush_t *Q1_TextureBrushes(bspbrush_t *brushlist, int modelnum)
{
	float area, largestarea;
	int i, n, texinfonum, sn, numbrushes, ofs;
	int bestfacenum, sidenodenum;
	side_t *side;
	q1_dmiptexlump_t *miptexlump;
	q1_miptex_t *miptex;
	bspbrush_t *brush, *nextbrush, *prevbrush, *newbrushes, *brushlistend;
	vec_t defaultvec[4] = {1, 0, 0, 0};

	if (!modelnum) qprintf("texturing brushes\n");
	if (!modelnum) qprintf("%5d brushes", numbrushes = 0);
	//get a pointer to the last brush in the list
	for (brushlistend = brushlist; brushlistend; brushlistend = brushlistend->next)
	{
		if (!brushlistend->next) break;
	} //end for
	//there's no previous brush when at the start of the list
	prevbrush = NULL;
	//go over the brush list
	for (brush = brushlist; brush; brush = nextbrush)
	{
		nextbrush = brush->next;
		//find a texinfo for every brush side
		for (sn = 0; sn < brush->numsides; sn++)
		{
			side = &brush->sides[sn];
			//
			if (side->flags & SFL_TEXTURED) continue;
			//number of the node that created this brush side
			sidenodenum = side->surf;	//see midwinding in Q1_SplitBrush
			//no face found yet
			bestfacenum = -1;
			//minimum face size
			largestarea = 1;
			//if optimizing the texture placement and not going for the
			//least number of brushes
			if (!lessbrushes)
			{
				for (i = 0; i < q1_numfaces; i++)
				{
					//the face must be in the same plane as the node plane that created
					//this brush side
					if (q1_dfaces[i].planenum == q1_dnodes[sidenodenum].planenum)
					{
						//get the area the face and the brush side overlap
						area = Q1_FaceOnWinding(&q1_dfaces[i], side->winding);
						//if this face overlaps the brush side winding more than previous faces
						if (area > largestarea)
						{
							//if there already was a face for texturing this brush side with
							//a different texture
							if (bestfacenum >= 0 &&
									(q1_dfaces[bestfacenum].texinfo != q1_dfaces[i].texinfo))
							{
								//split the brush to fit the texture
								newbrushes = Q1_SplitBrushWithFace(brush, &q1_dfaces[i]);
								//if new brushes where created
								if (newbrushes)
								{
									//remove the current brush from the list
									if (prevbrush) prevbrush->next = brush->next;
									else brushlist = brush->next;
									if (brushlistend == brush)
									{
										brushlistend = prevbrush;
										nextbrush = newbrushes;
									} //end if
									//add the new brushes to the end of the list
									if (brushlistend) brushlistend->next = newbrushes;
									else brushlist = newbrushes;
									//free the current brush
									FreeBrush(brush);
									//don't forget about the prevbrush pointer at the bottom of
									//the outer loop
									brush = prevbrush;
									//find the end of the list
									for (brushlistend = brushlist; brushlistend; brushlistend = brushlistend->next)
									{
										if (!brushlistend->next) break;
									} //end for
									break;
								} //end if
								else
								{
									Log_Write("brush %d: no real texture split", numbrushes);
								} //end else
							} //end if
							else
							{
								//best face for texturing this brush side
								bestfacenum = i;
							} //end else
						} //end if
					} //end if
				} //end for
				//if the brush was split the original brush is removed
				//and we just continue with the next one in the list
				if (i < q1_numfaces) break;
			} //end if
			else
			{
				//find the face with the largest overlap with this brush side
				//for texturing the brush side
				for (i = 0; i < q1_numfaces; i++)
				{
					//the face must be in the same plane as the node plane that created
					//this brush side
					if (q1_dfaces[i].planenum == q1_dnodes[sidenodenum].planenum)
					{
						//get the area the face and the brush side overlap
						area = Q1_FaceOnWinding(&q1_dfaces[i], side->winding);
						//if this face overlaps the brush side winding more than previous faces
						if (area > largestarea)
						{
							largestarea = area;
							bestfacenum = i;
						} //end if
					} //end if
				} //end for
			} //end else
			//if a face was found for texturing this brush side
			if (bestfacenum >= 0)
			{
				//set the MAP texinfo values
				texinfonum = q1_dfaces[bestfacenum].texinfo;
				for (n = 0; n < 4; n++)
				{
					map_texinfo[texinfonum].vecs[0][n] = q1_texinfo[texinfonum].vecs[0][n];
					map_texinfo[texinfonum].vecs[1][n] = q1_texinfo[texinfonum].vecs[1][n];
				} //end for
				//make sure the two vectors aren't of zero length otherwise use the default
				//vector to prevent a divide by zero in the map writing
				if (VectorLength(map_texinfo[texinfonum].vecs[0]) < 0.01)
					memcpy(map_texinfo[texinfonum].vecs[0], defaultvec, sizeof(defaultvec));
				if (VectorLength(map_texinfo[texinfonum].vecs[1]) < 0.01)
					memcpy(map_texinfo[texinfonum].vecs[1], defaultvec, sizeof(defaultvec));
				//
				map_texinfo[texinfonum].flags = q1_texinfo[texinfonum].flags;
				map_texinfo[texinfonum].value = 0; //Q1 and HL texinfos don't have a value
				//the mip texture
				miptexlump = (q1_dmiptexlump_t *) q1_dtexdata;
				ofs = miptexlump->dataofs[q1_texinfo[texinfonum].miptex];
				if ( ofs > q1_texdatasize ) {
					ofs = miptexlump->dataofs[0];
				}
				miptex = (q1_miptex_t *)((byte *)miptexlump + ofs);
				//get the mip texture name
				strcpy(map_texinfo[texinfonum].texture, miptex->name);
				//no animations in Quake1 and Half-Life mip textures
				map_texinfo[texinfonum].nexttexinfo = -1;
				//store the texinfo number
				side->texinfo = texinfonum;
				//
				if (texinfonum > map_numtexinfo) map_numtexinfo = texinfonum;
				//this side is textured
				side->flags |= SFL_TEXTURED;
			} //end if
			else
			{
				//no texture for this side
				side->texinfo = TEXINFO_NODE;
				//this side is textured
				side->flags |= SFL_TEXTURED;
			} //end if
		} //end for
		//
		if (!modelnum && prevbrush != brush) qprintf("\r%5d", ++numbrushes);
		//previous brush in the list
		prevbrush = brush;
	} //end for
	if (!modelnum) qprintf("\n");
	//return the new list with brushes
	return brushlist;
}
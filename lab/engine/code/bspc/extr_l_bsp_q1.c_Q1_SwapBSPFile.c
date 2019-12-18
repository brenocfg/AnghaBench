#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_14__ {int* headnode; int visleafs; int firstface; int numfaces; void** origin; void** maxs; void** mins; } ;
typedef  TYPE_1__ q1_dmodel_t ;
struct TYPE_15__ {int nummiptex; int* dataofs; } ;
typedef  TYPE_2__ q1_dmiptexlump_t ;
struct TYPE_21__ {int lightofs; int firstedge; void* numedges; void* side; void* planenum; void* texinfo; } ;
struct TYPE_20__ {int contents; int visofs; void* nummarksurfaces; void* firstmarksurface; void** maxs; void** mins; } ;
struct TYPE_19__ {int planenum; void* numfaces; void* firstface; void** children; void** maxs; void** mins; } ;
struct TYPE_18__ {int type; void* dist; void** normal; } ;
struct TYPE_17__ {void** point; } ;
struct TYPE_16__ {int miptex; int flags; void*** vecs; } ;
struct TYPE_13__ {int planenum; void** children; } ;
struct TYPE_12__ {void** v; } ;

/* Variables and functions */
 void* LittleFloat (void*) ; 
 void* LittleLong (int) ; 
 void* LittleShort (void*) ; 
 int Q1_MAX_MAP_HULLS ; 
 TYPE_11__* q1_dclipnodes ; 
 TYPE_10__* q1_dedges ; 
 TYPE_9__* q1_dfaces ; 
 TYPE_8__* q1_dleafs ; 
 void** q1_dmarksurfaces ; 
 TYPE_1__* q1_dmodels ; 
 TYPE_6__* q1_dnodes ; 
 TYPE_5__* q1_dplanes ; 
 int* q1_dsurfedges ; 
 scalar_t__ q1_dtexdata ; 
 TYPE_4__* q1_dvertexes ; 
 int q1_numclipnodes ; 
 int q1_numedges ; 
 int q1_numfaces ; 
 int q1_numleafs ; 
 int q1_nummarksurfaces ; 
 int q1_nummodels ; 
 int q1_numnodes ; 
 int q1_numplanes ; 
 int q1_numsurfedges ; 
 int q1_numtexinfo ; 
 int q1_numvertexes ; 
 scalar_t__ q1_texdatasize ; 
 TYPE_3__* q1_texinfo ; 

void Q1_SwapBSPFile (qboolean todisk)
{
	int i, j, k, c;
	q1_dmodel_t *d;
	q1_dmiptexlump_t *mtl;

	
// models	
	for (i=0 ; i<q1_nummodels ; i++)
	{
		d = &q1_dmodels[i];

		for (j=0 ; j<Q1_MAX_MAP_HULLS ; j++)
			d->headnode[j] = LittleLong (d->headnode[j]);

		d->visleafs = LittleLong (d->visleafs);
		d->firstface = LittleLong (d->firstface);
		d->numfaces = LittleLong (d->numfaces);
		
		for (j=0 ; j<3 ; j++)
		{
			d->mins[j] = LittleFloat(d->mins[j]);
			d->maxs[j] = LittleFloat(d->maxs[j]);
			d->origin[j] = LittleFloat(d->origin[j]);
		}
	}

//
// vertexes
//
	for (i=0 ; i<q1_numvertexes ; i++)
	{
		for (j=0 ; j<3 ; j++)
			q1_dvertexes[i].point[j] = LittleFloat(q1_dvertexes[i].point[j]);
	}
		
//
// planes
//	
	for (i=0 ; i<q1_numplanes ; i++)
	{
		for (j=0 ; j<3 ; j++)
			q1_dplanes[i].normal[j] = LittleFloat(q1_dplanes[i].normal[j]);
		q1_dplanes[i].dist = LittleFloat(q1_dplanes[i].dist);
		q1_dplanes[i].type = LittleLong(q1_dplanes[i].type);
	}
	
//
// texinfos
//	
	for (i=0 ; i<q1_numtexinfo ; i++)
	{
		for (j=0 ; j<2 ; j++)
		{
			for (k=0; k<4; k++)
			{
				q1_texinfo[i].vecs[j][k] = LittleFloat (q1_texinfo[i].vecs[j][k]);
			}
		}
		q1_texinfo[i].miptex = LittleLong(q1_texinfo[i].miptex);
		q1_texinfo[i].flags = LittleLong(q1_texinfo[i].flags);
	}
	
//
// faces
//
	for (i=0 ; i<q1_numfaces ; i++)
	{
		q1_dfaces[i].texinfo = LittleShort(q1_dfaces[i].texinfo);
		q1_dfaces[i].planenum = LittleShort(q1_dfaces[i].planenum);
		q1_dfaces[i].side = LittleShort(q1_dfaces[i].side);
		q1_dfaces[i].lightofs = LittleLong(q1_dfaces[i].lightofs);
		q1_dfaces[i].firstedge = LittleLong(q1_dfaces[i].firstedge);
		q1_dfaces[i].numedges = LittleShort(q1_dfaces[i].numedges);
	}

//
// nodes
//
	for (i=0 ; i<q1_numnodes ; i++)
	{
		q1_dnodes[i].planenum = LittleLong(q1_dnodes[i].planenum);
		for (j=0 ; j<3 ; j++)
		{
			q1_dnodes[i].mins[j] = LittleShort(q1_dnodes[i].mins[j]);
			q1_dnodes[i].maxs[j] = LittleShort(q1_dnodes[i].maxs[j]);
		}
		q1_dnodes[i].children[0] = LittleShort(q1_dnodes[i].children[0]);
		q1_dnodes[i].children[1] = LittleShort(q1_dnodes[i].children[1]);
		q1_dnodes[i].firstface = LittleShort(q1_dnodes[i].firstface);
		q1_dnodes[i].numfaces = LittleShort(q1_dnodes[i].numfaces);
	}

//
// leafs
//
	for (i=0 ; i<q1_numleafs ; i++)
	{
		q1_dleafs[i].contents = LittleLong(q1_dleafs[i].contents);
		for (j=0 ; j<3 ; j++)
		{
			q1_dleafs[i].mins[j] = LittleShort(q1_dleafs[i].mins[j]);
			q1_dleafs[i].maxs[j] = LittleShort(q1_dleafs[i].maxs[j]);
		}

		q1_dleafs[i].firstmarksurface = LittleShort(q1_dleafs[i].firstmarksurface);
		q1_dleafs[i].nummarksurfaces = LittleShort(q1_dleafs[i].nummarksurfaces);
		q1_dleafs[i].visofs = LittleLong(q1_dleafs[i].visofs);
	}

//
// clipnodes
//
	for (i=0 ; i<q1_numclipnodes ; i++)
	{
		q1_dclipnodes[i].planenum = LittleLong(q1_dclipnodes[i].planenum);
		q1_dclipnodes[i].children[0] = LittleShort(q1_dclipnodes[i].children[0]);
		q1_dclipnodes[i].children[1] = LittleShort(q1_dclipnodes[i].children[1]);
	}

//
// miptex
//
	if (q1_texdatasize)
	{
		mtl = (q1_dmiptexlump_t *)q1_dtexdata;
		if (todisk)
			c = mtl->nummiptex;
		else
			c = LittleLong(mtl->nummiptex);
		mtl->nummiptex = LittleLong (mtl->nummiptex);
		for (i=0 ; i<c ; i++)
			mtl->dataofs[i] = LittleLong(mtl->dataofs[i]);
	}
	
//
// marksurfaces
//
	for (i=0 ; i<q1_nummarksurfaces ; i++)
		q1_dmarksurfaces[i] = LittleShort(q1_dmarksurfaces[i]);

//
// surfedges
//
	for (i=0 ; i<q1_numsurfedges ; i++)
		q1_dsurfedges[i] = LittleLong(q1_dsurfedges[i]);

//
// edges
//
	for (i=0 ; i<q1_numedges ; i++)
	{
		q1_dedges[i].v[0] = LittleShort(q1_dedges[i].v[0]);
		q1_dedges[i].v[1] = LittleShort(q1_dedges[i].v[1]);
	}
}
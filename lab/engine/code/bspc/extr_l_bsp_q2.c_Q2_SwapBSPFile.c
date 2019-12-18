#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_20__ {int firstface; int numfaces; int headnode; void** origin; void** maxs; void** mins; } ;
typedef  TYPE_1__ dmodel_t ;
struct TYPE_27__ {int lightofs; int firstedge; void* numedges; void* side; void* planenum; void* texinfo; } ;
struct TYPE_26__ {int contents; void* numleafbrushes; void* firstleafbrush; void* numleaffaces; void* firstleafface; void** maxs; void** mins; void* area; void* cluster; } ;
struct TYPE_25__ {int planenum; int* children; void* numfaces; void* firstface; void** maxs; void** mins; } ;
struct TYPE_24__ {int type; void* dist; void** normal; } ;
struct TYPE_23__ {void** point; } ;
struct TYPE_22__ {int numclusters; int** bitofs; } ;
struct TYPE_21__ {int flags; int value; int nexttexinfo; void*** vecs; } ;
struct TYPE_19__ {int portalnum; int otherarea; } ;
struct TYPE_18__ {int numareaportals; int firstareaportal; } ;
struct TYPE_17__ {int firstside; int numsides; int contents; } ;
struct TYPE_16__ {void* texinfo; void* planenum; } ;
struct TYPE_15__ {void** v; } ;

/* Variables and functions */
 void* LittleFloat (void*) ; 
 void* LittleLong (int) ; 
 void* LittleShort (void*) ; 
 TYPE_14__* dareaportals ; 
 TYPE_13__* dareas ; 
 TYPE_12__* dbrushes ; 
 TYPE_11__* dbrushsides ; 
 TYPE_10__* dedges ; 
 TYPE_9__* dfaces ; 
 void** dleafbrushes ; 
 void** dleaffaces ; 
 TYPE_8__* dleafs ; 
 TYPE_1__* dmodels ; 
 TYPE_6__* dnodes ; 
 TYPE_5__* dplanes ; 
 int* dsurfedges ; 
 TYPE_4__* dvertexes ; 
 TYPE_3__* dvis ; 
 int numareaportals ; 
 int numareas ; 
 int numbrushes ; 
 int numbrushsides ; 
 int numedges ; 
 int numfaces ; 
 int numleafbrushes ; 
 int numleaffaces ; 
 int numleafs ; 
 int nummodels ; 
 int numnodes ; 
 int numplanes ; 
 int numsurfedges ; 
 int numtexinfo ; 
 int numvertexes ; 
 TYPE_2__* texinfo ; 

void Q2_SwapBSPFile (qboolean todisk)
{
	int				i, j, k;
	dmodel_t		*d;

	
// models	
	for (i=0 ; i<nummodels ; i++)
	{
		d = &dmodels[i];

		d->firstface = LittleLong (d->firstface);
		d->numfaces = LittleLong (d->numfaces);
		d->headnode = LittleLong (d->headnode);
		
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
	for (i=0 ; i<numvertexes ; i++)
	{
		for (j=0 ; j<3 ; j++)
			dvertexes[i].point[j] = LittleFloat (dvertexes[i].point[j]);
	}
		
//
// planes
//	
	for (i=0 ; i<numplanes ; i++)
	{
		for (j=0 ; j<3 ; j++)
			dplanes[i].normal[j] = LittleFloat (dplanes[i].normal[j]);
		dplanes[i].dist = LittleFloat (dplanes[i].dist);
		dplanes[i].type = LittleLong (dplanes[i].type);
	}
	
//
// texinfos
//	
	for (i=0 ; i<numtexinfo ; i++)
	{
		for (j=0 ; j<2 ; j++)
		{
			for (k=0; k<4; k++)
			{
				texinfo[i].vecs[j][k] = LittleFloat (texinfo[i].vecs[j][k]);
			}
		}
		texinfo[i].flags = LittleLong (texinfo[i].flags);
		texinfo[i].value = LittleLong (texinfo[i].value);
		texinfo[i].nexttexinfo = LittleLong (texinfo[i].nexttexinfo);
	}
	
//
// faces
//
	for (i=0 ; i<numfaces ; i++)
	{
		dfaces[i].texinfo = LittleShort (dfaces[i].texinfo);
		dfaces[i].planenum = LittleShort (dfaces[i].planenum);
		dfaces[i].side = LittleShort (dfaces[i].side);
		dfaces[i].lightofs = LittleLong (dfaces[i].lightofs);
		dfaces[i].firstedge = LittleLong (dfaces[i].firstedge);
		dfaces[i].numedges = LittleShort (dfaces[i].numedges);
	}

//
// nodes
//
	for (i=0 ; i<numnodes ; i++)
	{
		dnodes[i].planenum = LittleLong (dnodes[i].planenum);
		for (j=0 ; j<3 ; j++)
		{
			dnodes[i].mins[j] = LittleShort (dnodes[i].mins[j]);
			dnodes[i].maxs[j] = LittleShort (dnodes[i].maxs[j]);
		}
		dnodes[i].children[0] = LittleLong (dnodes[i].children[0]);
		dnodes[i].children[1] = LittleLong (dnodes[i].children[1]);
		dnodes[i].firstface = LittleShort (dnodes[i].firstface);
		dnodes[i].numfaces = LittleShort (dnodes[i].numfaces);
	}

//
// leafs
//
	for (i=0 ; i<numleafs ; i++)
	{
		dleafs[i].contents = LittleLong (dleafs[i].contents);
		dleafs[i].cluster = LittleShort (dleafs[i].cluster);
		dleafs[i].area = LittleShort (dleafs[i].area);
		for (j=0 ; j<3 ; j++)
		{
			dleafs[i].mins[j] = LittleShort (dleafs[i].mins[j]);
			dleafs[i].maxs[j] = LittleShort (dleafs[i].maxs[j]);
		}

		dleafs[i].firstleafface = LittleShort (dleafs[i].firstleafface);
		dleafs[i].numleaffaces = LittleShort (dleafs[i].numleaffaces);
		dleafs[i].firstleafbrush = LittleShort (dleafs[i].firstleafbrush);
		dleafs[i].numleafbrushes = LittleShort (dleafs[i].numleafbrushes);
	}

//
// leaffaces
//
	for (i=0 ; i<numleaffaces ; i++)
		dleaffaces[i] = LittleShort (dleaffaces[i]);

//
// leafbrushes
//
	for (i=0 ; i<numleafbrushes ; i++)
		dleafbrushes[i] = LittleShort (dleafbrushes[i]);

//
// surfedges
//
	for (i=0 ; i<numsurfedges ; i++)
		dsurfedges[i] = LittleLong (dsurfedges[i]);

//
// edges
//
	for (i=0 ; i<numedges ; i++)
	{
		dedges[i].v[0] = LittleShort (dedges[i].v[0]);
		dedges[i].v[1] = LittleShort (dedges[i].v[1]);
	}

//
// brushes
//
	for (i=0 ; i<numbrushes ; i++)
	{
		dbrushes[i].firstside = LittleLong (dbrushes[i].firstside);
		dbrushes[i].numsides = LittleLong (dbrushes[i].numsides);
		dbrushes[i].contents = LittleLong (dbrushes[i].contents);
	}

//
// areas
//
	for (i=0 ; i<numareas ; i++)
	{
		dareas[i].numareaportals = LittleLong (dareas[i].numareaportals);
		dareas[i].firstareaportal = LittleLong (dareas[i].firstareaportal);
	}

//
// areasportals
//
	for (i=0 ; i<numareaportals ; i++)
	{
		dareaportals[i].portalnum = LittleLong (dareaportals[i].portalnum);
		dareaportals[i].otherarea = LittleLong (dareaportals[i].otherarea);
	}

//
// brushsides
//
	for (i=0 ; i<numbrushsides ; i++)
	{
		dbrushsides[i].planenum = LittleShort (dbrushsides[i].planenum);
		dbrushsides[i].texinfo = LittleShort (dbrushsides[i].texinfo);
	}

//
// visibility
//
	if (todisk)
		j = dvis->numclusters;
	else
		j = LittleLong(dvis->numclusters);
	dvis->numclusters = LittleLong (dvis->numclusters);
	for (i=0 ; i<j ; i++)
	{
		dvis->bitofs[i][0] = LittleLong (dvis->bitofs[i][0]);
		dvis->bitofs[i][1] = LittleLong (dvis->bitofs[i][1]);
	}
}
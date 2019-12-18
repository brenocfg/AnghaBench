#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  fileHandle_t ;
typedef  int /*<<< orphan*/  aas_vertex_t ;
typedef  int /*<<< orphan*/  aas_reachability_t ;
typedef  int /*<<< orphan*/  aas_portalindex_t ;
typedef  int /*<<< orphan*/  aas_portal_t ;
typedef  int /*<<< orphan*/  aas_plane_t ;
typedef  int /*<<< orphan*/  aas_node_t ;
struct TYPE_8__ {void* bspchecksum; void* version; void* ident; } ;
typedef  TYPE_1__ aas_header_t ;
typedef  int /*<<< orphan*/  aas_faceindex_t ;
typedef  int /*<<< orphan*/  aas_face_t ;
typedef  int /*<<< orphan*/  aas_edgeindex_t ;
typedef  int /*<<< orphan*/  aas_edge_t ;
typedef  int /*<<< orphan*/  aas_cluster_t ;
typedef  int /*<<< orphan*/  aas_bbox_t ;
typedef  int /*<<< orphan*/  aas_areasettings_t ;
typedef  int /*<<< orphan*/  aas_area_t ;
struct TYPE_10__ {int numbboxes; int numvertexes; int numplanes; int numedges; int edgeindexsize; int numfaces; int faceindexsize; int numareas; int numareasettings; int reachabilitysize; int numnodes; int numportals; int portalindexsize; int numclusters; int /*<<< orphan*/  clusters; int /*<<< orphan*/  portalindex; int /*<<< orphan*/  portals; int /*<<< orphan*/  nodes; int /*<<< orphan*/  reachability; int /*<<< orphan*/  areasettings; int /*<<< orphan*/  areas; int /*<<< orphan*/  faceindex; int /*<<< orphan*/  faces; int /*<<< orphan*/  edgeindex; int /*<<< orphan*/  edges; int /*<<< orphan*/  planes; int /*<<< orphan*/  vertexes; int /*<<< orphan*/  bboxes; int /*<<< orphan*/  bspchecksum; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* FS_FCloseFile ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* FS_Write ) (TYPE_1__*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* FS_Seek ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,char*) ;int /*<<< orphan*/  (* FS_FOpenFile ) (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AASID ; 
 int /*<<< orphan*/  AASLUMP_AREAS ; 
 int /*<<< orphan*/  AASLUMP_AREASETTINGS ; 
 int /*<<< orphan*/  AASLUMP_BBOXES ; 
 int /*<<< orphan*/  AASLUMP_CLUSTERS ; 
 int /*<<< orphan*/  AASLUMP_EDGEINDEX ; 
 int /*<<< orphan*/  AASLUMP_EDGES ; 
 int /*<<< orphan*/  AASLUMP_FACEINDEX ; 
 int /*<<< orphan*/  AASLUMP_FACES ; 
 int /*<<< orphan*/  AASLUMP_NODES ; 
 int /*<<< orphan*/  AASLUMP_PLANES ; 
 int /*<<< orphan*/  AASLUMP_PORTALINDEX ; 
 int /*<<< orphan*/  AASLUMP_PORTALS ; 
 int /*<<< orphan*/  AASLUMP_REACHABILITY ; 
 int /*<<< orphan*/  AASLUMP_VERTEXES ; 
 int /*<<< orphan*/  AASVERSION ; 
 int /*<<< orphan*/  AAS_DData (unsigned char*,int) ; 
 int /*<<< orphan*/  AAS_SwapAASData () ; 
 int /*<<< orphan*/  AAS_WriteAASLump (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int AAS_WriteAASLump_offset ; 
 int /*<<< orphan*/  Com_Memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FS_SEEK_SET ; 
 int /*<<< orphan*/  FS_WRITE ; 
 void* LittleLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 TYPE_5__ aasworld ; 
 TYPE_4__ botimport ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub2 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ) ; 

qboolean AAS_WriteAASFile(char *filename)
{
	aas_header_t header;
	fileHandle_t fp;

	botimport.Print(PRT_MESSAGE, "writing %s\n", filename);
	//swap the aas data
	AAS_SwapAASData();
	//initialize the file header
	Com_Memset(&header, 0, sizeof(aas_header_t));
	header.ident = LittleLong(AASID);
	header.version = LittleLong(AASVERSION);
	header.bspchecksum = LittleLong(aasworld.bspchecksum);
	//open a new file
	botimport.FS_FOpenFile( filename, &fp, FS_WRITE );
	if (!fp)
	{
		botimport.Print(PRT_ERROR, "error opening %s\n", filename);
		return qfalse;
	} //end if
	//write the header
	botimport.FS_Write(&header, sizeof(aas_header_t), fp);
	AAS_WriteAASLump_offset = sizeof(aas_header_t);
	//add the data lumps to the file
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_BBOXES, aasworld.bboxes,
		aasworld.numbboxes * sizeof(aas_bbox_t))) return qfalse;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_VERTEXES, aasworld.vertexes,
		aasworld.numvertexes * sizeof(aas_vertex_t))) return qfalse;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_PLANES, aasworld.planes,
		aasworld.numplanes * sizeof(aas_plane_t))) return qfalse;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_EDGES, aasworld.edges,
		aasworld.numedges * sizeof(aas_edge_t))) return qfalse;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_EDGEINDEX, aasworld.edgeindex,
		aasworld.edgeindexsize * sizeof(aas_edgeindex_t))) return qfalse;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_FACES, aasworld.faces,
		aasworld.numfaces * sizeof(aas_face_t))) return qfalse;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_FACEINDEX, aasworld.faceindex,
		aasworld.faceindexsize * sizeof(aas_faceindex_t))) return qfalse;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_AREAS, aasworld.areas,
		aasworld.numareas * sizeof(aas_area_t))) return qfalse;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_AREASETTINGS, aasworld.areasettings,
		aasworld.numareasettings * sizeof(aas_areasettings_t))) return qfalse;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_REACHABILITY, aasworld.reachability,
		aasworld.reachabilitysize * sizeof(aas_reachability_t))) return qfalse;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_NODES, aasworld.nodes,
		aasworld.numnodes * sizeof(aas_node_t))) return qfalse;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_PORTALS, aasworld.portals,
		aasworld.numportals * sizeof(aas_portal_t))) return qfalse;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_PORTALINDEX, aasworld.portalindex,
		aasworld.portalindexsize * sizeof(aas_portalindex_t))) return qfalse;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_CLUSTERS, aasworld.clusters,
		aasworld.numclusters * sizeof(aas_cluster_t))) return qfalse;
	//rewrite the header with the added lumps
	botimport.FS_Seek(fp, 0, FS_SEEK_SET);
	AAS_DData((unsigned char *) &header + 8, sizeof(aas_header_t) - 8);
	botimport.FS_Write(&header, sizeof(aas_header_t), fp);
	//close the file
	botimport.FS_FCloseFile(fp);
	return qtrue;
}
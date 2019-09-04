#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int numareas; int numclusters; int numportalcache; int numareacache; int size; struct TYPE_9__* next; void* clustercrc; void* areacrc; int /*<<< orphan*/  version; int /*<<< orphan*/  ident; } ;
typedef  TYPE_1__ routecacheheader_t ;
typedef  int /*<<< orphan*/  fileHandle_t ;
typedef  TYPE_1__ aas_routingcache_t ;
struct TYPE_10__ {int numareas; } ;
typedef  TYPE_3__ aas_cluster_t ;
typedef  int /*<<< orphan*/  aas_area_t ;
struct TYPE_12__ {int numareas; int numclusters; TYPE_1__*** clusterareacache; TYPE_3__* clusters; TYPE_1__** portalcache; scalar_t__ areas; int /*<<< orphan*/  mapname; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;int /*<<< orphan*/  (* FS_FCloseFile ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* FS_Write ) (TYPE_1__*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* FS_FOpenFile ) (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_Error (char*,char*) ; 
 void* CRC_ProcessString (unsigned char*,int) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_WRITE ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/  RCID ; 
 int /*<<< orphan*/  RCVERSION ; 
 TYPE_8__ aasworld ; 
 TYPE_7__ botimport ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,char*,int) ; 

void AAS_WriteRouteCache(void)
{
	int i, j, numportalcache, numareacache, totalsize;
	aas_routingcache_t *cache;
	aas_cluster_t *cluster;
	fileHandle_t fp;
	char filename[MAX_QPATH];
	routecacheheader_t routecacheheader;

	numportalcache = 0;
	for (i = 0; i < aasworld.numareas; i++)
	{
		for (cache = aasworld.portalcache[i]; cache; cache = cache->next)
		{
			numportalcache++;
		} //end for
	} //end for
	numareacache = 0;
	for (i = 0; i < aasworld.numclusters; i++)
	{
		cluster = &aasworld.clusters[i];
		for (j = 0; j < cluster->numareas; j++)
		{
			for (cache = aasworld.clusterareacache[i][j]; cache; cache = cache->next)
			{
				numareacache++;
			} //end for
		} //end for
	} //end for
	// open the file for writing
	Com_sprintf(filename, MAX_QPATH, "maps/%s.rcd", aasworld.mapname);
	botimport.FS_FOpenFile( filename, &fp, FS_WRITE );
	if (!fp)
	{
		AAS_Error("Unable to open file: %s\n", filename);
		return;
	} //end if
	//create the header
	routecacheheader.ident = RCID;
	routecacheheader.version = RCVERSION;
	routecacheheader.numareas = aasworld.numareas;
	routecacheheader.numclusters = aasworld.numclusters;
	routecacheheader.areacrc = CRC_ProcessString( (unsigned char *)aasworld.areas, sizeof(aas_area_t) * aasworld.numareas );
	routecacheheader.clustercrc = CRC_ProcessString( (unsigned char *)aasworld.clusters, sizeof(aas_cluster_t) * aasworld.numclusters );
	routecacheheader.numportalcache = numportalcache;
	routecacheheader.numareacache = numareacache;
	//write the header
	botimport.FS_Write(&routecacheheader, sizeof(routecacheheader_t), fp);
	//
	totalsize = 0;
	//write all the cache
	for (i = 0; i < aasworld.numareas; i++)
	{
		for (cache = aasworld.portalcache[i]; cache; cache = cache->next)
		{
			botimport.FS_Write(cache, cache->size, fp);
			totalsize += cache->size;
		} //end for
	} //end for
	for (i = 0; i < aasworld.numclusters; i++)
	{
		cluster = &aasworld.clusters[i];
		for (j = 0; j < cluster->numareas; j++)
		{
			for (cache = aasworld.clusterareacache[i][j]; cache; cache = cache->next)
			{
				botimport.FS_Write(cache, cache->size, fp);
				totalsize += cache->size;
			} //end for
		} //end for
	} //end for
	// write the visareas
	/*
	for (i = 0; i < aasworld.numareas; i++)
	{
		if (!aasworld.areavisibility[i]) {
			size = 0;
			botimport.FS_Write(&size, sizeof(int), fp);
			continue;
		}
		AAS_DecompressVis( aasworld.areavisibility[i], aasworld.numareas, aasworld.decompressedvis );
		size = AAS_CompressVis( aasworld.decompressedvis, aasworld.numareas, aasworld.decompressedvis );
		botimport.FS_Write(&size, sizeof(int), fp);
		botimport.FS_Write(aasworld.decompressedvis, size, fp);
	}
	*/
	//
	botimport.FS_FCloseFile(fp);
	botimport.Print(PRT_MESSAGE, "\nroute cache written to %s\n", filename);
	botimport.Print(PRT_MESSAGE, "written %d bytes of routing cache\n", totalsize);
}
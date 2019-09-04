#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * headnode; } ;
typedef  TYPE_1__ tree_t ;
typedef  int /*<<< orphan*/  node_t ;

/* Variables and functions */
 int /*<<< orphan*/  CreateVisPortals_r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Error (char*,char*) ; 
 int /*<<< orphan*/  MakeHeadnodePortals (TYPE_1__*) ; 
 int /*<<< orphan*/  NumberLeafs_r (int /*<<< orphan*/ *) ; 
 char* PORTALFILE ; 
 int /*<<< orphan*/  SaveClusters_r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tree_FreePortals_r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WritePortalFile_r (int /*<<< orphan*/ *) ; 
 int clusterleaf ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int num_visclusters ; 
 int num_visportals ; 
 int /*<<< orphan*/  pf ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 char* source ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void WritePortalFile (tree_t *tree)
{
	char	filename[1024];
	node_t *headnode;

	qprintf ("--- WritePortalFile ---\n");

	headnode = tree->headnode;
	num_visclusters = 0;
	num_visportals = 0;

	Tree_FreePortals_r (headnode);

	MakeHeadnodePortals (tree);

	CreateVisPortals_r (headnode);

// set the cluster field in every leaf and count the total number of portals

	NumberLeafs_r (headnode);
	
// write the file
	sprintf (filename, "%s.prt", source);
	printf ("writing %s\n", filename);
	pf = fopen (filename, "w");
	if (!pf)
		Error ("Error opening %s", filename);
		
	fprintf (pf, "%s\n", PORTALFILE);
	fprintf (pf, "%i\n", num_visclusters);
	fprintf (pf, "%i\n", num_visportals);

	qprintf ("%5i visclusters\n", num_visclusters);
	qprintf ("%5i visportals\n", num_visportals);

	WritePortalFile_r (headnode);

	fclose (pf);

	// we need to store the clusters out now because ordering
	// issues made us do this after writebsp...
	clusterleaf = 1;
	SaveClusters_r (headnode);
}
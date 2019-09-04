#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  texinfo_t ;
typedef  int /*<<< orphan*/  dheader_t ;
struct TYPE_8__ {scalar_t__ ident; scalar_t__ version; TYPE_1__* lumps; } ;
struct TYPE_7__ {int filelen; int fileofs; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ BSPVERSION ; 
 int /*<<< orphan*/  Error (char*,char*,...) ; 
 int /*<<< orphan*/  FreeMemory (TYPE_2__*) ; 
 TYPE_2__* GetMemory (int) ; 
 scalar_t__ IDBSPHEADER ; 
 size_t LUMP_TEXINFO ; 
 int LittleLong (int) ; 
 int /*<<< orphan*/  Q2_SwapBSPFile (int) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* header ; 
 int numtexinfo ; 
 TYPE_2__* texinfo ; 

void	Q2_LoadBSPFileTexinfo (char *filename)
{
	int			i;
	FILE		*f;
	int		length, ofs;

	header = GetMemory(sizeof(dheader_t));

	f = fopen (filename, "rb");
	fread (header, sizeof(dheader_t), 1, f);

// swap the header
	for (i=0 ; i< sizeof(dheader_t)/4 ; i++)
		((int *)header)[i] = LittleLong ( ((int *)header)[i]);

	if (header->ident != IDBSPHEADER)
		Error ("%s is not a IBSP file", filename);
	if (header->version != BSPVERSION)
		Error ("%s is version %i, not %i", filename, header->version, BSPVERSION);


	length = header->lumps[LUMP_TEXINFO].filelen;
	ofs = header->lumps[LUMP_TEXINFO].fileofs;

	fseek (f, ofs, SEEK_SET);
	fread (texinfo, length, 1, f);
	fclose (f);

	numtexinfo = length / sizeof(texinfo_t);

	FreeMemory(header);		// everything has been copied out
		
	Q2_SwapBSPFile (false);
}
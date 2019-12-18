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
typedef  int /*<<< orphan*/  sin_texinfo_t ;
typedef  int /*<<< orphan*/  sin_dheader_t ;
struct TYPE_8__ {scalar_t__ ident; scalar_t__ version; TYPE_1__* lumps; } ;
struct TYPE_7__ {int filelen; int fileofs; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char*,...) ; 
 int /*<<< orphan*/  FreeMemory (TYPE_2__*) ; 
 TYPE_2__* GetMemory (int) ; 
 int LittleLong (int) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ SINGAME_BSPHEADER ; 
 scalar_t__ SINGAME_BSPVERSION ; 
 scalar_t__ SIN_BSPHEADER ; 
 scalar_t__ SIN_BSPVERSION ; 
 size_t SIN_LUMP_TEXINFO ; 
 int /*<<< orphan*/  Sin_SwapBSPFile (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* header ; 
 int sin_numtexinfo ; 
 TYPE_2__* sin_texinfo ; 

void	Sin_LoadBSPFileTexinfo (char *filename)
{
	int			i;
	FILE		*f;
	int		length, ofs;

	header = GetMemory(sizeof(sin_dheader_t));

	f = fopen (filename, "rb");
	fread (header, sizeof(sin_dheader_t), 1, f);

// swap the header
	for (i=0 ; i< sizeof(sin_dheader_t)/4 ; i++)
		((int *)header)[i] = LittleLong ( ((int *)header)[i]);

	if (header->ident != SIN_BSPHEADER && header->ident != SINGAME_BSPHEADER)
		Error ("%s is not a IBSP file", filename);
	if (header->version != SIN_BSPVERSION && header->version != SINGAME_BSPVERSION)
		Error ("%s is version %i, not %i", filename, header->version, SIN_BSPVERSION);


	length = header->lumps[SIN_LUMP_TEXINFO].filelen;
	ofs = header->lumps[SIN_LUMP_TEXINFO].fileofs;

	fseek (f, ofs, SEEK_SET);
	fread (sin_texinfo, length, 1, f);
	fclose (f);

	sin_numtexinfo = length / sizeof(sin_texinfo_t);

	FreeMemory(header);		// everything has been copied out
		
	Sin_SwapBSPFile (false);
}
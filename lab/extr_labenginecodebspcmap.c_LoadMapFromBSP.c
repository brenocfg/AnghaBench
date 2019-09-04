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
struct quakefile_s {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; int /*<<< orphan*/  filename; } ;
struct TYPE_3__ {int ident; int version; } ;
typedef  TYPE_1__ idheader_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,int,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  HL_AllocMaxBSP () ; 
 int HL_BSPVERSION ; 
 int /*<<< orphan*/  HL_FreeMaxBSP () ; 
 int /*<<< orphan*/  HL_LoadMapFromBSP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* LittleLong (int) ; 
 int /*<<< orphan*/  Q1_AllocMaxBSP () ; 
 int Q1_BSPVERSION ; 
 int /*<<< orphan*/  Q1_FreeMaxBSP () ; 
 int /*<<< orphan*/  Q1_LoadMapFromBSP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q2_AllocMaxBSP () ; 
 int Q2_BSPHEADER ; 
 scalar_t__ Q2_BSPVERSION ; 
 int /*<<< orphan*/  Q2_FreeMaxBSP () ; 
 int /*<<< orphan*/  Q2_LoadMapFromBSP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Q3_BSP_IDENT ; 
 scalar_t__ Q3_BSP_VERSION ; 
 int /*<<< orphan*/  Q3_FreeMaxBSP () ; 
 int /*<<< orphan*/  Q3_LoadMapFromBSP (struct quakefile_s*) ; 
 int QF_BSP_IDENT ; 
 scalar_t__ QF_BSP_VERSION ; 
 int QL_BSP_IDENT ; 
 scalar_t__ QL_BSP_VERSION ; 
 int ReadQuakeFile (struct quakefile_s*,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ResetMapLoading () ; 
 int SINGAME_BSPHEADER ; 
 scalar_t__ SINGAME_BSPVERSION ; 
 int SIN_BSPHEADER ; 
 scalar_t__ SIN_BSPVERSION ; 
 int /*<<< orphan*/  Sin_AllocMaxBSP () ; 
 int /*<<< orphan*/  Sin_FreeMaxBSP () ; 
 int /*<<< orphan*/  Sin_LoadMapFromBSP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int LoadMapFromBSP(struct quakefile_s *qf)
{
	idheader_t idheader;

	if (ReadQuakeFile(qf, &idheader, 0, sizeof(idheader_t)) != sizeof(idheader_t))
	{
		return false;
	} //end if

	idheader.ident = LittleLong(idheader.ident);
	idheader.version = LittleLong(idheader.version);
	//QuakeLive BSP file
	if (idheader.ident == QL_BSP_IDENT && idheader.version == QL_BSP_VERSION)
	{
		ResetMapLoading();
		Q3_LoadMapFromBSP(qf);
		Q3_FreeMaxBSP();
	} //end if
	//Qfusion BSP file
	else if (idheader.ident == QF_BSP_IDENT && idheader.version == QF_BSP_VERSION)
	{
		ResetMapLoading();
		Q3_LoadMapFromBSP(qf);
		Q3_FreeMaxBSP();
	} //end if
	//Quake3 BSP file
	else if (idheader.ident == Q3_BSP_IDENT && idheader.version == Q3_BSP_VERSION)
	{
		ResetMapLoading();
		Q3_LoadMapFromBSP(qf);
		Q3_FreeMaxBSP();
	} //end if
	//Quake2 BSP file
	else if (idheader.ident == Q2_BSPHEADER && idheader.version == Q2_BSPVERSION)
	{
		ResetMapLoading();
		Q2_AllocMaxBSP();
		Q2_LoadMapFromBSP(qf->filename, qf->offset, qf->length);
		Q2_FreeMaxBSP();
	} //endif
	//Sin BSP file
	else if ((idheader.ident == SIN_BSPHEADER && idheader.version == SIN_BSPVERSION) ||
				//the dorks gave the same format another ident and verions
				(idheader.ident == SINGAME_BSPHEADER && idheader.version == SINGAME_BSPVERSION))
	{
		ResetMapLoading();
		Sin_AllocMaxBSP();
		Sin_LoadMapFromBSP(qf->filename, qf->offset, qf->length);
		Sin_FreeMaxBSP();
	} //end if
	//the Quake1 bsp files don't have a ident only a version
	else if (idheader.ident == Q1_BSPVERSION)
	{
		ResetMapLoading();
		Q1_AllocMaxBSP();
		Q1_LoadMapFromBSP(qf->filename, qf->offset, qf->length);
		Q1_FreeMaxBSP();
	} //end if
	//Half-Life also only uses a version number
	else if (idheader.ident == HL_BSPVERSION)
	{
		ResetMapLoading();
		HL_AllocMaxBSP();
		HL_LoadMapFromBSP(qf->filename, qf->offset, qf->length);
		HL_FreeMaxBSP();
	} //end if
	else
	{
		Error("unknown BSP format %c%c%c%c, version %d\n",
										(idheader.ident & 0xFF),
										((idheader.ident >> 8) & 0xFF),
										((idheader.ident >> 16) & 0xFF),
										((idheader.ident >> 24) & 0xFF), idheader.version);
		return false;
	} //end if
	//
	return true;
}
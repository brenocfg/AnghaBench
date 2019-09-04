#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
struct TYPE_6__ {scalar_t__ deviceSupportsGamma; } ;
struct TYPE_5__ {int /*<<< orphan*/  integer; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* Hunk_FreeTempMemory ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * RB_ReadPixels (int,int,int,int,size_t*,int*) ; 
 int /*<<< orphan*/  RE_SaveJPG (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  R_GammaCorrect (int /*<<< orphan*/ *,size_t) ; 
 TYPE_3__ glConfig ; 
 TYPE_2__* r_screenshotJpegQuality ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void RB_TakeScreenshotJPEG(int x, int y, int width, int height, char *fileName)
{
	byte *buffer;
	size_t offset = 0, memcount;
	int padlen;

	buffer = RB_ReadPixels(x, y, width, height, &offset, &padlen);
	memcount = (width * 3 + padlen) * height;

	// gamma correct
	if(glConfig.deviceSupportsGamma)
		R_GammaCorrect(buffer + offset, memcount);

	RE_SaveJPG(fileName, r_screenshotJpegQuality->integer, width, height, buffer + offset, padlen);
	ri.Hunk_FreeTempMemory(buffer);
}
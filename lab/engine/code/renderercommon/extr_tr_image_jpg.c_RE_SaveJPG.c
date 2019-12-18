#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
struct TYPE_2__ {int /*<<< orphan*/  (* Hunk_FreeTempMemory ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* FS_WriteFile ) (char*,int /*<<< orphan*/ *,size_t) ;int /*<<< orphan*/ * (* Hunk_AllocateTempMemory ) (size_t) ;} ;

/* Variables and functions */
 size_t RE_SaveJPGToBuffer (int /*<<< orphan*/ *,size_t,int,int,int,int /*<<< orphan*/ *,int) ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/ * stub1 (size_t) ; 
 int /*<<< orphan*/  stub2 (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 

void RE_SaveJPG(char * filename, int quality, int image_width, int image_height, byte *image_buffer, int padding)
{
  byte *out;
  size_t bufSize;

  bufSize = image_width * image_height * 3;
  out = ri.Hunk_AllocateTempMemory(bufSize);

  bufSize = RE_SaveJPGToBuffer(out, bufSize, quality, image_width, image_height, image_buffer, padding);
  ri.FS_WriteFile(filename, out, bufSize);

  ri.Hunk_FreeTempMemory(out);
}
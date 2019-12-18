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
struct BufferedFile {scalar_t__ Buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* Free ) (struct BufferedFile*) ;int /*<<< orphan*/  (* FS_FreeFile ) (scalar_t__) ;} ;

/* Variables and functions */
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct BufferedFile*) ; 

__attribute__((used)) static void CloseBufferedFile(struct BufferedFile *BF)
{
	if(BF)
	{
		if(BF->Buffer)
		{
			ri.FS_FreeFile(BF->Buffer);
		}

		ri.Free(BF);
	}
}
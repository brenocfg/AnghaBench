#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct BufferedFile {unsigned int BytesLeft; int /*<<< orphan*/  Ptr; } ;
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean BufferedFileSkip(struct BufferedFile *BF, unsigned Offset)
{
	/*
	 *  input verification
	 */

	if(!BF)
	{
		return(qfalse);
	}

	/*
	 *  We can only skip to the end of the BufferedFile.
	 */

	if(Offset > BF->BytesLeft)
	{
		return(qfalse);
	}

	/*
	 *  lower the pointer and counter.
	 */

	BF->Ptr       += Offset;
	BF->BytesLeft -= Offset;

	return(qtrue);
}
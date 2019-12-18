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
struct BufferedFile {unsigned int BytesLeft; void* Ptr; } ;

/* Variables and functions */

__attribute__((used)) static void *BufferedFileRead(struct BufferedFile *BF, unsigned Length)
{
	void *RetVal;

	/*
	 *  input verification
	 */

	if(!(BF && Length))
	{
		return(NULL);
	}

	/*
	 *  not enough bytes left
	 */

	if(Length > BF->BytesLeft)
	{
		return(NULL);
	}

	/*
	 *  the pointer to the requested data
	 */

	RetVal = BF->Ptr;

	/*
	 *  Raise the pointer and counter.
	 */

	BF->Ptr       += Length;
	BF->BytesLeft -= Length;

	return(RetVal);
}
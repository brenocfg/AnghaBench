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
struct BufferedFile {scalar_t__ Length; scalar_t__ BytesLeft; int /*<<< orphan*/ * Buffer; int /*<<< orphan*/ * Ptr; } ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_2__ {scalar_t__ (* FS_ReadFile ) (char*,void**) ;int /*<<< orphan*/  (* Free ) (struct BufferedFile*) ;struct BufferedFile* (* Malloc ) (int) ;} ;

/* Variables and functions */
 TYPE_1__ ri ; 
 struct BufferedFile* stub1 (int) ; 
 scalar_t__ stub2 (char*,void**) ; 
 int /*<<< orphan*/  stub3 (struct BufferedFile*) ; 

__attribute__((used)) static struct BufferedFile *ReadBufferedFile(const char *name)
{
	struct BufferedFile *BF;
	union {
		byte *b;
		void *v;
	} buffer;

	/*
	 *  input verification
	 */

	if(!name)
	{
		return(NULL);
	}

	/*
	 *  Allocate control struct.
	 */

	BF = ri.Malloc(sizeof(struct BufferedFile));
	if(!BF)
	{
		return(NULL);
	}

	/*
	 *  Initialize the structs components.
	 */

	BF->Length    = 0;
	BF->Buffer    = NULL;
	BF->Ptr       = NULL;
	BF->BytesLeft = 0;

	/*
	 *  Read the file.
	 */

	BF->Length = ri.FS_ReadFile((char *) name, &buffer.v);
	BF->Buffer = buffer.b;

	/*
	 *  Did we get it? Is it big enough?
	 */

	if(!(BF->Buffer && (BF->Length > 0)))
	{
		ri.Free(BF);

		return(NULL);
	}

	/*
	 *  Set the pointers and counters.
	 */

	BF->Ptr       = BF->Buffer;
	BF->BytesLeft = BF->Length;

	return(BF);
}
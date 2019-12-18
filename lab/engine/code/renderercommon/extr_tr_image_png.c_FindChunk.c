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
typedef  scalar_t__ uint32_t ;
struct PNG_ChunkHeader {int /*<<< orphan*/  Type; int /*<<< orphan*/  Length; } ;
struct BufferedFile {int dummy; } ;
typedef  scalar_t__ qboolean ;

/* Variables and functions */
 scalar_t__ BigLong (int /*<<< orphan*/ ) ; 
 struct PNG_ChunkHeader* BufferedFileRead (struct BufferedFile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferedFileRewind (struct BufferedFile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferedFileSkip (struct BufferedFile*,scalar_t__) ; 
 scalar_t__ PNG_ChunkCRC_Size ; 
 int /*<<< orphan*/  PNG_ChunkHeader_Size ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

__attribute__((used)) static qboolean FindChunk(struct BufferedFile *BF, uint32_t ChunkType)
{
	struct PNG_ChunkHeader *CH;

	uint32_t Length;
	uint32_t Type;

	/*
	 *  input verification
	 */

	if(!BF)
	{
		return(qfalse);
	}

	/*
	 *  cycle trough the chunks
	 */

	while(qtrue)
	{
		/*
		 *  Read the chunk-header.
		 */

		CH = BufferedFileRead(BF, PNG_ChunkHeader_Size);
		if(!CH)
		{
			return(qfalse);
		}

		/*
		 *  Do not swap the original types
		 *  they might be needed later.
		 */

		Length = BigLong(CH->Length);
		Type   = BigLong(CH->Type);

		/*
		 *  We found it!
		 */

		if(Type == ChunkType)
		{
			/*
			 *  Rewind to the start of the chunk.
			 */

			BufferedFileRewind(BF, PNG_ChunkHeader_Size);

			break;
		}
		else
		{
			/*
			 *  Skip the rest of the chunk.
			 */

			if(Length)
			{
				if(!BufferedFileSkip(BF, Length + PNG_ChunkCRC_Size))
				{
					return(qfalse);
				}  
			}
		}
	}

	return(qtrue);
}
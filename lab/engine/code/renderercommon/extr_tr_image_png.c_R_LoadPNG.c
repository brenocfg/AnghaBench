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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct PNG_Chunk_IHDR {scalar_t__ CompressionMethod; scalar_t__ FilterMethod; int InterlaceMethod; int ColourType; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;
struct PNG_ChunkHeader {int /*<<< orphan*/  Type; int /*<<< orphan*/  Length; } ;
struct BufferedFile {int dummy; } ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int byte ;
struct TYPE_2__ {int* (* Malloc ) (int) ;int /*<<< orphan*/  (* Free ) (int*) ;int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,char const*) ;} ;
typedef  int /*<<< orphan*/  PNG_ChunkCRC ;

/* Variables and functions */
 int BigLong (int /*<<< orphan*/ ) ; 
 void* BufferedFileRead (struct BufferedFile*,int) ; 
 int /*<<< orphan*/  BufferedFileRewind (struct BufferedFile*,int) ; 
 int /*<<< orphan*/  BufferedFileSkip (struct BufferedFile*,int) ; 
 int /*<<< orphan*/  CloseBufferedFile (struct BufferedFile*) ; 
 int /*<<< orphan*/  DecodeImageInterlaced (struct PNG_Chunk_IHDR*,int*,int*,int,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  DecodeImageNonInterlaced (struct PNG_Chunk_IHDR*,int*,int*,int,int /*<<< orphan*/ ,int*,int*) ; 
 int DecompressIDATs (struct BufferedFile*,int**) ; 
 scalar_t__ FindChunk (struct BufferedFile*,int) ; 
 int INT_MAX ; 
 int PNG_ChunkCRC_Size ; 
 int PNG_ChunkHeader_Size ; 
 int PNG_ChunkType_IHDR ; 
 int PNG_ChunkType_PLTE ; 
 int PNG_ChunkType_tRNS ; 
 int PNG_Chunk_IHDR_Size ; 
#define  PNG_ColourType_Grey 132 
#define  PNG_ColourType_Indexed 131 
#define  PNG_ColourType_True 130 
 scalar_t__ PNG_CompressionMethod_0 ; 
 scalar_t__ PNG_FilterMethod_0 ; 
#define  PNG_InterlaceMethod_Interlaced 129 
#define  PNG_InterlaceMethod_NonInterlaced 128 
 int /*<<< orphan*/  PNG_Signature ; 
 int PNG_Signature_Size ; 
 int /*<<< orphan*/  PRINT_WARNING ; 
 int Q3IMAGE_BYTESPERPIXEL ; 
 struct BufferedFile* ReadBufferedFile (char const*) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stub10 (int*) ; 
 int* stub2 (int) ; 
 int /*<<< orphan*/  stub3 (int*) ; 
 int /*<<< orphan*/  stub4 (int*) ; 
 int /*<<< orphan*/  stub5 (int*) ; 
 int /*<<< orphan*/  stub6 (int*) ; 
 int /*<<< orphan*/  stub7 (int*) ; 
 int /*<<< orphan*/  stub8 (int*) ; 
 int /*<<< orphan*/  stub9 (int*) ; 

void R_LoadPNG(const char *name, byte **pic, int *width, int *height)
{
	struct BufferedFile *ThePNG;
	byte *OutBuffer;
	uint8_t *Signature;
	struct PNG_ChunkHeader *CH;
	uint32_t ChunkHeaderLength;
	uint32_t ChunkHeaderType;
	struct PNG_Chunk_IHDR *IHDR;
	uint32_t IHDR_Width;
	uint32_t IHDR_Height;
	PNG_ChunkCRC *CRC;
	uint8_t *InPal;
	uint8_t *DecompressedData;
	uint32_t DecompressedDataLength;
	uint32_t i;

	/*
	 *  palette with 256 RGBA entries
	 */

	uint8_t OutPal[1024];

	/*
	 *  transparent colour from the tRNS chunk
	 */

	qboolean HasTransparentColour = qfalse;
	uint8_t TransparentColour[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

	/*
	 *  input verification
	 */

	if(!(name && pic))
	{
		return;
	}

	/*
	 *  Zero out return values.
	 */

	*pic = NULL;

	if(width)
	{
		*width = 0;
	}

	if(height)
	{
		*height = 0;
	}

	/*
	 *  Read the file.
	 */

	ThePNG = ReadBufferedFile(name);
	if(!ThePNG)
	{
		return;
	}           

	/*
	 *  Read the siganture of the file.
	 */

	Signature = BufferedFileRead(ThePNG, PNG_Signature_Size);
	if(!Signature)
	{
		CloseBufferedFile(ThePNG);

		return;
	}

	/*
	 *  Is it a PNG?
	 */

	if(memcmp(Signature, PNG_Signature, PNG_Signature_Size))
	{
		CloseBufferedFile(ThePNG);

		return; 
	}

	/*
	 *  Read the first chunk-header.
	 */

	CH = BufferedFileRead(ThePNG, PNG_ChunkHeader_Size);
	if(!CH)
	{
		CloseBufferedFile(ThePNG);

		return; 
	}

	/*
	 *  PNG multi-byte types are in Big Endian
	 */

	ChunkHeaderLength = BigLong(CH->Length);
	ChunkHeaderType   = BigLong(CH->Type);

	/*
	 *  Check if the first chunk is an IHDR.
	 */

	if(!((ChunkHeaderType == PNG_ChunkType_IHDR) && (ChunkHeaderLength == PNG_Chunk_IHDR_Size)))
	{
		CloseBufferedFile(ThePNG);

		return; 
	}

	/*
	 *  Read the IHDR.
	 */ 

	IHDR = BufferedFileRead(ThePNG, PNG_Chunk_IHDR_Size);
	if(!IHDR)
	{
		CloseBufferedFile(ThePNG);

		return; 
	}

	/*
	 *  Read the CRC for IHDR
	 */

	CRC = BufferedFileRead(ThePNG, PNG_ChunkCRC_Size);
	if(!CRC)
	{
		CloseBufferedFile(ThePNG);

		return; 
	}

	/*
	 *  Here we could check the CRC if we wanted to.
	 */

	/*
	 *  multi-byte type swapping
	 */

	IHDR_Width  = BigLong(IHDR->Width);
	IHDR_Height = BigLong(IHDR->Height);

	/*
	 *  Check if Width and Height are valid.
	 */

	if(!((IHDR_Width > 0) && (IHDR_Height > 0))
	|| IHDR_Width > INT_MAX / Q3IMAGE_BYTESPERPIXEL / IHDR_Height)
	{
		CloseBufferedFile(ThePNG);

		ri.Printf( PRINT_WARNING, "%s: invalid image size\n", name );

		return; 
	}

	/*
	 *  Do we need to check if the dimensions of the image are valid for Quake3?
	 */

	/*
	 *  Check if CompressionMethod and FilterMethod are valid.
	 */

	if(!((IHDR->CompressionMethod == PNG_CompressionMethod_0) && (IHDR->FilterMethod == PNG_FilterMethod_0)))
	{
		CloseBufferedFile(ThePNG);

		return; 
	}

	/*
	 *  Check if InterlaceMethod is valid.
	 */

	if(!((IHDR->InterlaceMethod == PNG_InterlaceMethod_NonInterlaced)  || (IHDR->InterlaceMethod == PNG_InterlaceMethod_Interlaced)))
	{
		CloseBufferedFile(ThePNG);

		return;
	}

	/*
	 *  Read palette for an indexed image.
	 */

	if(IHDR->ColourType == PNG_ColourType_Indexed)
	{
		/*
		 *  We need the palette first.
		 */

		if(!FindChunk(ThePNG, PNG_ChunkType_PLTE))
		{
			CloseBufferedFile(ThePNG);

			return;
		}

		/*
		 *  Read the chunk-header.
		 */

		CH = BufferedFileRead(ThePNG, PNG_ChunkHeader_Size);
		if(!CH)
		{
			CloseBufferedFile(ThePNG);

			return; 
		}

		/*
		 *  PNG multi-byte types are in Big Endian
		 */

		ChunkHeaderLength = BigLong(CH->Length);
		ChunkHeaderType   = BigLong(CH->Type);

		/*
		 *  Check if the chunk is a PLTE.
		 */

		if(!(ChunkHeaderType == PNG_ChunkType_PLTE))
		{
			CloseBufferedFile(ThePNG);

			return; 
		}

		/*
		 *  Check if Length is divisible by 3
		 */

		if(ChunkHeaderLength % 3)
		{
			CloseBufferedFile(ThePNG);

			return;   
		}

		/*
		 *  Read the raw palette data
		 */

		InPal = BufferedFileRead(ThePNG, ChunkHeaderLength);
		if(!InPal)
		{
			CloseBufferedFile(ThePNG);

			return; 
		}

		/*
		 *  Read the CRC for the palette
		 */

		CRC = BufferedFileRead(ThePNG, PNG_ChunkCRC_Size);
		if(!CRC)
		{
			CloseBufferedFile(ThePNG);

			return; 
		}

		/*
		 *  Set some default values.
		 */

		for(i = 0; i < 256; i++)
		{
			OutPal[i * Q3IMAGE_BYTESPERPIXEL + 0] = 0x00;
			OutPal[i * Q3IMAGE_BYTESPERPIXEL + 1] = 0x00;
			OutPal[i * Q3IMAGE_BYTESPERPIXEL + 2] = 0x00;
			OutPal[i * Q3IMAGE_BYTESPERPIXEL + 3] = 0xFF;  
		}

		/*
		 *  Convert to the Quake3 RGBA-format.
		 */

		for(i = 0; i < (ChunkHeaderLength / 3); i++)
		{
			OutPal[i * Q3IMAGE_BYTESPERPIXEL + 0] = InPal[i*3+0];
			OutPal[i * Q3IMAGE_BYTESPERPIXEL + 1] = InPal[i*3+1];
			OutPal[i * Q3IMAGE_BYTESPERPIXEL + 2] = InPal[i*3+2];
			OutPal[i * Q3IMAGE_BYTESPERPIXEL + 3] = 0xFF;
		}
	}

	/*
	 *  transparency information is sometimes stored in a tRNS chunk
	 */

	/*
	 *  Let's see if there is a tRNS chunk
	 */

	if(FindChunk(ThePNG, PNG_ChunkType_tRNS))
	{
		uint8_t *Trans;

		/*
		 *  Read the chunk-header.
		 */

		CH = BufferedFileRead(ThePNG, PNG_ChunkHeader_Size);
		if(!CH)
		{
			CloseBufferedFile(ThePNG);

			return; 
		}

		/*
		 *  PNG multi-byte types are in Big Endian
		 */

		ChunkHeaderLength = BigLong(CH->Length);
		ChunkHeaderType   = BigLong(CH->Type);

		/*
		 *  Check if the chunk is a tRNS.
		 */

		if(!(ChunkHeaderType == PNG_ChunkType_tRNS))
		{
			CloseBufferedFile(ThePNG);

			return; 
		}

		/*
		 *  Read the transparency information.
		 */

		Trans = BufferedFileRead(ThePNG, ChunkHeaderLength);
		if(!Trans)
		{
			CloseBufferedFile(ThePNG);

			return;  
		}

		/*
		 *  Read the CRC.
		 */

		CRC = BufferedFileRead(ThePNG, PNG_ChunkCRC_Size);
		if(!CRC)
		{
			CloseBufferedFile(ThePNG);

			return; 
		}

		/*
		 *  Only for Grey, True and Indexed ColourType should tRNS exist.
		 */

		switch(IHDR->ColourType)
		{
			case PNG_ColourType_Grey :
			{
				if(ChunkHeaderLength != 2)
				{
					CloseBufferedFile(ThePNG);

					return;    
				}

				HasTransparentColour = qtrue;

				/*
				 *  Grey can have one colour which is completely transparent.
				 *  This colour is always stored in 16 bits.
				 */

				TransparentColour[0] = Trans[0];
				TransparentColour[1] = Trans[1];

				break;
			}

			case PNG_ColourType_True :
			{
				if(ChunkHeaderLength != 6)
				{
					CloseBufferedFile(ThePNG);

					return;    
				}

				HasTransparentColour = qtrue;

				/*
				 *  True can have one colour which is completely transparent.
				 *  This colour is always stored in 16 bits.
				 */

				TransparentColour[0] = Trans[0];
				TransparentColour[1] = Trans[1];
				TransparentColour[2] = Trans[2];
				TransparentColour[3] = Trans[3];
				TransparentColour[4] = Trans[4];
				TransparentColour[5] = Trans[5];

				break;
			}

			case PNG_ColourType_Indexed :
			{
				/*
				 *  Maximum of 256 one byte transparency entries.
				 */

				if(ChunkHeaderLength > 256)
				{
					CloseBufferedFile(ThePNG);

					return;    
				}

				HasTransparentColour = qtrue;

				/*
				 *  alpha values for palette entries
				 */

				for(i = 0; i < ChunkHeaderLength; i++)
				{
					OutPal[i * Q3IMAGE_BYTESPERPIXEL + 3] = Trans[i];
				}

				break;
			}

			/*
			 *  All other ColourTypes should not have tRNS chunks
			 */

			default :
			{
				CloseBufferedFile(ThePNG);

				return;
			}
		} 
	}

	/*
	 *  Rewind to the start of the file.
	 */

	if(!BufferedFileRewind(ThePNG, -1))
	{
		CloseBufferedFile(ThePNG);

		return; 
	}

	/*
	 *  Skip the signature
	 */

	if(!BufferedFileSkip(ThePNG, PNG_Signature_Size))
	{
		CloseBufferedFile(ThePNG);

		return; 
	}

	/*
	 *  Decompress all IDAT chunks
	 */

	DecompressedDataLength = DecompressIDATs(ThePNG, &DecompressedData);
	if(!(DecompressedDataLength && DecompressedData))
	{
		CloseBufferedFile(ThePNG);

		return;
	}

	/*
	 *  Allocate output buffer.
	 */

	OutBuffer = ri.Malloc(IHDR_Width * IHDR_Height * Q3IMAGE_BYTESPERPIXEL); 
	if(!OutBuffer)
	{
		ri.Free(DecompressedData); 
		CloseBufferedFile(ThePNG);

		return;  
	}

	/*
	 *  Interlaced and Non-interlaced images need to be handled differently.
	 */

	switch(IHDR->InterlaceMethod)
	{
		case PNG_InterlaceMethod_NonInterlaced :
		{
			if(!DecodeImageNonInterlaced(IHDR, OutBuffer, DecompressedData, DecompressedDataLength, HasTransparentColour, TransparentColour, OutPal))
			{
				ri.Free(OutBuffer); 
				ri.Free(DecompressedData); 
				CloseBufferedFile(ThePNG);

				return;
			}

			break;
		}

		case PNG_InterlaceMethod_Interlaced :
		{
			if(!DecodeImageInterlaced(IHDR, OutBuffer, DecompressedData, DecompressedDataLength, HasTransparentColour, TransparentColour, OutPal))
			{
				ri.Free(OutBuffer); 
				ri.Free(DecompressedData); 
				CloseBufferedFile(ThePNG);

				return;
			}

			break;
		}

		default :
		{
			ri.Free(OutBuffer); 
			ri.Free(DecompressedData); 
			CloseBufferedFile(ThePNG);

			return;
		}
	}

	/*
	 *  update the pointer to the image data
	 */

	*pic = OutBuffer;

	/*
	 *  Fill width and height.
	 */

	if(width)
	{
		*width = IHDR_Width;
	}

	if(height)
	{
		*height = IHDR_Height;
	}

	/*
	 *  DecompressedData is not needed anymore.
	 */

	ri.Free(DecompressedData); 

	/*
	 *  We have all data, so close the file.
	 */

	CloseBufferedFile(ThePNG);
}
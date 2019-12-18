#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  BufferLim; int /*<<< orphan*/  Buffer; } ;
typedef  int /*<<< orphan*/  SizeT ;
typedef  TYPE_1__ CLzmaDecoderState ;

/* Variables and functions */
 int LzmaDecode (TYPE_1__*,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  datalen ; 
 int /*<<< orphan*/  lzma_callback ; 

__attribute__((used)) static int decompress_data(CLzmaDecoderState *vs, unsigned char *outStream,
			SizeT outSize)
{
	SizeT op;

#if 0
	vs->Buffer = data;
	vs->BufferLim = datalen;
#endif

	return LzmaDecode(vs, &lzma_callback, outStream, outSize, &op);
}
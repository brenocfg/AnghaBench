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
struct TYPE_3__ {int /*<<< orphan*/ * Probs; } ;
typedef  int SizeT ;
typedef  int /*<<< orphan*/  CProb ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int LZMA_RESULT_OK ; 
 int LzmaDecode (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,unsigned char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * lzma_data ; 
 int /*<<< orphan*/  lzma_datasize ; 
 int /*<<< orphan*/  lzma_outsize ; 
 TYPE_1__ lzma_state ; 
 scalar_t__ workspace ; 

__attribute__((used)) static int lzma_decompress(unsigned char *outStream)
{
	SizeT ip, op;
	int ret;

	lzma_state.Probs = (CProb *) workspace;

	ret = LzmaDecode(&lzma_state, lzma_data, lzma_datasize, &ip, outStream,
			 lzma_outsize, &op);

	if (ret != LZMA_RESULT_OK) {
		int i;

		DBG("LzmaDecode error %d at %08x, osize:%d ip:%d op:%d\n",
		    ret, lzma_data + ip, lzma_outsize, ip, op);

		for (i = 0; i < 16; i++)
			DBG("%02x ", lzma_data[ip + i]);

		DBG("\n");
	}

	return ret;
}
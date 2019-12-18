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
struct TYPE_3__ {int litLength; size_t matchLength; size_t offset; } ;
typedef  TYPE_1__ ZSTD_Sequence ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void FUZ_decodeSequences(BYTE* dst, ZSTD_Sequence* seqs, size_t seqsSize, BYTE* src, size_t size)
{
    size_t i;
    size_t j;
    for(i = 0; i < seqsSize - 1; ++i) {
        assert(dst + seqs[i].litLength + seqs[i].matchLength < dst + size);
        assert(src + seqs[i].litLength + seqs[i].matchLength < src + size);

        memcpy(dst, src, seqs[i].litLength);
        dst += seqs[i].litLength;
        src += seqs[i].litLength;
        size -= seqs[i].litLength;

        for (j = 0; j < seqs[i].matchLength; ++j)
            dst[j] = dst[j - seqs[i].offset];
        dst += seqs[i].matchLength;
        src += seqs[i].matchLength;
        size -= seqs[i].matchLength;
    }
    memcpy(dst, src, size);
}
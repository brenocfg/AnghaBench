#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_1__ frame_t ;
typedef  int /*<<< orphan*/  dictInfo ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 size_t writeLiteralsBlock (int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 
 size_t writeSequencesBlock (int /*<<< orphan*/ *,TYPE_1__*,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t writeCompressedBlock(U32* seed, frame_t* frame, size_t contentSize, dictInfo info)
{
    BYTE* const blockStart = (BYTE*)frame->data;
    size_t literalsSize;
    size_t nbSeq;

    DISPLAYLEVEL(4, "  compressed block:\n");

    literalsSize = writeLiteralsBlock(seed, frame, contentSize);

    DISPLAYLEVEL(4, "   literals size: %u\n", (unsigned)literalsSize);

    nbSeq = writeSequencesBlock(seed, frame, contentSize, literalsSize, info);

    DISPLAYLEVEL(4, "   number of sequences: %u\n", (unsigned)nbSeq);

    return (BYTE*)frame->data - blockStart;
}
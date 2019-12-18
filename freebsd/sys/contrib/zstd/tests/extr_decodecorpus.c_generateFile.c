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
typedef  scalar_t__ genType_e ;
struct TYPE_4__ {scalar_t__ srcStart; scalar_t__ src; scalar_t__ dataStart; scalar_t__ data; } ;
typedef  TYPE_1__ frame_t ;
typedef  int /*<<< orphan*/  dictInfo ;
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,unsigned int) ; 
 int /*<<< orphan*/  generateCompressedBlock (scalar_t__,TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  generateFrame (scalar_t__,TYPE_1__*,int /*<<< orphan*/  const) ; 
 scalar_t__ gt_frame ; 
 int /*<<< orphan*/  initDictInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outputBuffer (scalar_t__,int,char const* const) ; 

__attribute__((used)) static int generateFile(U32 seed, const char* const path,
                        const char* const origPath, genType_e genType)
{
    frame_t fr;

    DISPLAY("seed: %u\n", (unsigned)seed);

    {   dictInfo const info = initDictInfo(0, 0, NULL, 0);
        if (genType == gt_frame) {
            generateFrame(seed, &fr, info);
        } else {
            generateCompressedBlock(seed, &fr, info);
        }
    }
    outputBuffer(fr.dataStart, (BYTE*)fr.data - (BYTE*)fr.dataStart, path);
    if (origPath) {
        outputBuffer(fr.srcStart, (BYTE*)fr.src - (BYTE*)fr.srcStart, origPath);
    }
    return 0;
}
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
typedef  int /*<<< orphan*/  params ;
typedef  int /*<<< orphan*/  ZDICT_params_t ;

/* Variables and functions */
 size_t ZDICT_addEntropyTablesFromBuffer_advanced (void*,size_t,size_t,void const*,size_t const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

size_t ZDICT_addEntropyTablesFromBuffer(void* dictBuffer, size_t dictContentSize, size_t dictBufferCapacity,
                                  const void* samplesBuffer, const size_t* samplesSizes, unsigned nbSamples)
{
    ZDICT_params_t params;
    memset(&params, 0, sizeof(params));
    return ZDICT_addEntropyTablesFromBuffer_advanced(dictBuffer, dictContentSize, dictBufferCapacity,
                                                     samplesBuffer, samplesSizes, nbSamples,
                                                     params);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {size_t count; TYPE_4__* region; } ;
typedef  TYPE_5__ mpiMemReq_t ;
struct TYPE_11__ {int eventLogSize; int IOPeventLogSize; } ;
struct TYPE_14__ {int numInboundQueues; int numOutboundQueues; TYPE_2__* outboundQueues; TYPE_1__* inboundQueues; TYPE_3__ mainConfig; } ;
typedef  TYPE_6__ mpiConfig_t ;
typedef  int /*<<< orphan*/  bit8 ;
typedef  size_t bit32 ;
struct TYPE_12__ {int numElements; int elementSize; int totalLength; int alignment; void* type; } ;
struct TYPE_10__ {size_t numElements; size_t elementSize; } ;
struct TYPE_9__ {size_t numElements; size_t elementSize; } ;

/* Variables and functions */
 void* AGSA_CACHED_DMA_MEM ; 
 void* AGSA_DMA_MEM ; 
 size_t MAX_QUEUE_EACH_MEM ; 
 int /*<<< orphan*/  SA_ASSERT (int,char*) ; 
 int /*<<< orphan*/  SA_DBG2 (char*) ; 

void mpiRequirementsGet(mpiConfig_t* config, mpiMemReq_t* memoryRequirement)
{
  bit32 qIdx, numq;
  mpiMemReq_t* memoryMap;
  SA_DBG2(("Entering function:mpiRequirementsGet\n"));
  SA_ASSERT((NULL != config), "config argument cannot be null");

  memoryMap = memoryRequirement;
  memoryMap->count = 0;

  /* MPI Memory region 0 for MSGU(AAP1) Event Log for fw */
  memoryMap->region[memoryMap->count].numElements = 1;
  memoryMap->region[memoryMap->count].elementSize = sizeof(bit8) * config->mainConfig.eventLogSize;
  memoryMap->region[memoryMap->count].totalLength = sizeof(bit8) * config->mainConfig.eventLogSize;
  memoryMap->region[memoryMap->count].alignment = 32;
  memoryMap->region[memoryMap->count].type = AGSA_DMA_MEM;
  SA_DBG2(("mpiRequirementsGet:eventLogSize region[%d] 0x%X\n",memoryMap->count,memoryMap->region[memoryMap->count].totalLength ));
  memoryMap->count++;

  SA_DBG2(("mpiRequirementsGet:eventLogSize region[%d] 0x%X\n",memoryMap->count,memoryMap->region[memoryMap->count].totalLength ));
  /* MPI Memory region 1 for IOP Event Log for fw */
  memoryMap->region[memoryMap->count].numElements = 1;
  memoryMap->region[memoryMap->count].elementSize = sizeof(bit8) * config->mainConfig.IOPeventLogSize;
  memoryMap->region[memoryMap->count].totalLength = sizeof(bit8) * config->mainConfig.IOPeventLogSize;
  memoryMap->region[memoryMap->count].alignment = 32;
  memoryMap->region[memoryMap->count].type = AGSA_DMA_MEM;
  SA_DBG2(("mpiRequirementsGet:IOPeventLogSize region[%d] 0x%X\n",memoryMap->count,memoryMap->region[memoryMap->count].totalLength ));
  memoryMap->count++;

  /* MPI Memory region 2 for consumer Index of inbound queues */
  memoryMap->region[memoryMap->count].numElements = 1;
  memoryMap->region[memoryMap->count].elementSize = sizeof(bit32) * config->numInboundQueues;
  memoryMap->region[memoryMap->count].totalLength = sizeof(bit32) * config->numInboundQueues;
  memoryMap->region[memoryMap->count].alignment = 4;
  memoryMap->region[memoryMap->count].type = AGSA_DMA_MEM;
  SA_DBG2(("mpiRequirementsGet:numInboundQueues region[%d] 0x%X\n",memoryMap->count,memoryMap->region[memoryMap->count].totalLength ));
  memoryMap->count++;

  /* MPI Memory region 3 for producer Index of outbound queues */
  memoryMap->region[memoryMap->count].numElements = 1;
  memoryMap->region[memoryMap->count].elementSize = sizeof(bit32) * config->numOutboundQueues;
  memoryMap->region[memoryMap->count].totalLength = sizeof(bit32) * config->numOutboundQueues;
  memoryMap->region[memoryMap->count].alignment = 4;
  memoryMap->region[memoryMap->count].type = AGSA_DMA_MEM;
  SA_DBG2(("mpiRequirementsGet:numOutboundQueues region[%d] 0x%X\n",memoryMap->count,memoryMap->region[memoryMap->count].totalLength ));
  memoryMap->count++;

  /* MPI Memory regions 4, ... for the inbound queues - depends on configuration */
  numq = 0;
  for(qIdx = 0; qIdx < config->numInboundQueues; qIdx++)
  {
    if(0 != config->inboundQueues[qIdx].numElements)
    {
        bit32 memSize = config->inboundQueues[qIdx].numElements * config->inboundQueues[qIdx].elementSize;
        bit32 remainder = memSize & 127;

        /* Calculate the size of this queue padded to 128 bytes */
        if (remainder > 0)
        {
            memSize += (128 - remainder);
        }

        if (numq == 0)
        {
            memoryMap->region[memoryMap->count].numElements = 1;
            memoryMap->region[memoryMap->count].elementSize = memSize;
            memoryMap->region[memoryMap->count].totalLength = memSize;
            memoryMap->region[memoryMap->count].alignment = 128;
            memoryMap->region[memoryMap->count].type = AGSA_CACHED_DMA_MEM;
        }
        else
        {
            memoryMap->region[memoryMap->count].elementSize += memSize;
            memoryMap->region[memoryMap->count].totalLength += memSize;
        }

        numq++;

        if ((0 == ((qIdx + 1) % MAX_QUEUE_EACH_MEM)) ||
            (qIdx == (bit32)(config->numInboundQueues - 1)))
        {
            SA_DBG2(("mpiRequirementsGet: (inboundQueues) memoryMap->region[%d].elementSize = %d\n",
                     memoryMap->count, memoryMap->region[memoryMap->count].elementSize));
            SA_DBG2(("mpiRequirementsGet: (inboundQueues) memoryMap->region[%d].numElements = %d\n",
                     memoryMap->count, memoryMap->region[memoryMap->count].numElements));

            memoryMap->count++;
            numq = 0;
        }
    }
  }

  /* MPI Memory regions for the outbound queues - depends on configuration */
  numq = 0;
  for(qIdx = 0; qIdx < config->numOutboundQueues; qIdx++)
  {
    if(0 != config->outboundQueues[qIdx].numElements)
    {
        bit32 memSize = config->outboundQueues[qIdx].numElements * config->outboundQueues[qIdx].elementSize;
        bit32 remainder = memSize & 127;

        /* Calculate the size of this queue padded to 128 bytes */
        if (remainder > 0)
        {
            memSize += (128 - remainder);
        }

        if (numq == 0)
        {
            memoryMap->region[memoryMap->count].numElements = 1;
            memoryMap->region[memoryMap->count].elementSize = memSize;
            memoryMap->region[memoryMap->count].totalLength = memSize;
            memoryMap->region[memoryMap->count].alignment = 128;
            memoryMap->region[memoryMap->count].type = AGSA_CACHED_DMA_MEM;
        }
        else
        {
            memoryMap->region[memoryMap->count].elementSize += memSize;
            memoryMap->region[memoryMap->count].totalLength += memSize;
        }

        numq++;

        if ((0 == ((qIdx + 1) % MAX_QUEUE_EACH_MEM)) ||
            (qIdx ==  (bit32)(config->numOutboundQueues - 1)))
        {
            SA_DBG2(("mpiRequirementsGet: (outboundQueues) memoryMap->region[%d].elementSize = %d\n",
                     memoryMap->count, memoryMap->region[memoryMap->count].elementSize));
            SA_DBG2(("mpiRequirementsGet: (outboundQueues) memoryMap->region[%d].numElements = %d\n",
                     memoryMap->count, memoryMap->region[memoryMap->count].numElements));


            memoryMap->count++;
            numq = 0;
        }
    }
  }

}
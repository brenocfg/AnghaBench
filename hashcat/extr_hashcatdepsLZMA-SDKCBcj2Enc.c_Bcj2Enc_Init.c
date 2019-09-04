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
struct TYPE_3__ {int range; int cacheSize; int* probs; scalar_t__ flushPos; scalar_t__ tempPos; int /*<<< orphan*/  relatLimit; scalar_t__ fileSize; scalar_t__ fileIp; scalar_t__ ip; scalar_t__ low; scalar_t__ cache; scalar_t__ prevByte; int /*<<< orphan*/  finishMode; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ CBcj2Enc ;

/* Variables and functions */
 int /*<<< orphan*/  BCJ2_ENC_FINISH_MODE_CONTINUE ; 
 int /*<<< orphan*/  BCJ2_ENC_STATE_OK ; 
 int /*<<< orphan*/  BCJ2_RELAT_LIMIT ; 
 int kBitModelTotal ; 

void Bcj2Enc_Init(CBcj2Enc *p)
{
  unsigned i;

  p->state = BCJ2_ENC_STATE_OK;
  p->finishMode = BCJ2_ENC_FINISH_MODE_CONTINUE;

  p->prevByte = 0;

  p->cache = 0;
  p->range = 0xFFFFFFFF;
  p->low = 0;
  p->cacheSize = 1;

  p->ip = 0;

  p->fileIp = 0;
  p->fileSize = 0;
  p->relatLimit = BCJ2_RELAT_LIMIT;

  p->tempPos = 0;

  p->flushPos = 0;

  for (i = 0; i < sizeof(p->probs) / sizeof(p->probs[0]); i++)
    p->probs[i] = kBitModelTotal >> 1;
}
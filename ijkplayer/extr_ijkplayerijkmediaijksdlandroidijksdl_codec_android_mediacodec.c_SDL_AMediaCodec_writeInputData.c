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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* func_writeInputData ) (TYPE_1__*,size_t,int /*<<< orphan*/  const*,size_t) ;} ;
typedef  TYPE_1__ SDL_AMediaCodec ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/  (*) (TYPE_1__*,size_t,int /*<<< orphan*/  const*,size_t)) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,size_t,int /*<<< orphan*/  const*,size_t) ; 

ssize_t SDL_AMediaCodec_writeInputData(SDL_AMediaCodec* acodec, size_t idx, const uint8_t *data, size_t size)
{
    assert(acodec->func_writeInputData);
    return acodec->func_writeInputData(acodec, idx, data, size);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
struct TYPE_6__ {scalar_t__ totalInBytes; scalar_t__ streamEnd; } ;
typedef  TYPE_2__ ZWRAP_CCtx ;
struct TYPE_5__ {scalar_t__ adler; scalar_t__ total_out; scalar_t__ total_in; scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WRAPPERC (char*) ; 
 int Z_OK ; 
 int deflateReset (TYPE_1__*) ; 
 int /*<<< orphan*/  g_ZWRAP_useZSTDcompression ; 

int ZWRAP_deflateReset_keepDict(z_streamp strm)
{
    LOG_WRAPPERC("- ZWRAP_deflateReset_keepDict\n");
    if (!g_ZWRAP_useZSTDcompression)
        return deflateReset(strm);

    { ZWRAP_CCtx* zwc = (ZWRAP_CCtx*) strm->state;
      if (zwc) {
          zwc->streamEnd = 0;
          zwc->totalInBytes = 0;
      }
    }

    strm->total_in = 0;
    strm->total_out = 0;
    strm->adler = 0;
    return Z_OK;
}
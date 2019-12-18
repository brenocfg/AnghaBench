#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ time_t ;
struct TYPE_7__ {int accessible; } ;
typedef  TYPE_2__ status_ctx_t ;
struct TYPE_8__ {TYPE_2__* status_ctx; TYPE_4__* cpt_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;
struct TYPE_9__ {TYPE_1__* cpt_buf; } ;
typedef  TYPE_4__ cpt_ctx_t ;
struct TYPE_6__ {scalar_t__ timestamp; scalar_t__ cracked; } ;

/* Variables and functions */
 int CPT_CACHE ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int status_get_cpt_cur_min (const hashcat_ctx_t *hashcat_ctx)
{
  const cpt_ctx_t    *cpt_ctx    = hashcat_ctx->cpt_ctx;
  const status_ctx_t *status_ctx = hashcat_ctx->status_ctx;

  if (status_ctx->accessible == false) return 0;

  const time_t now = time (NULL);

  int cpt_cur_min = 0;

  for (int i = 0; i < CPT_CACHE; i++)
  {
    const u32       cracked   = cpt_ctx->cpt_buf[i].cracked;
    const time_t timestamp = cpt_ctx->cpt_buf[i].timestamp;

    if ((timestamp + 60) > now)
    {
      cpt_cur_min += cracked;
    }
  }

  return cpt_cur_min;
}
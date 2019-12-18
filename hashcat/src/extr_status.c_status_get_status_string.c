#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int devices_status; int checkpoint_shutdown; } ;
typedef  TYPE_1__ status_ctx_t ;
struct TYPE_5__ {TYPE_1__* status_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
#define  STATUS_ABORTED 140 
#define  STATUS_ABORTED_CHECKPOINT 139 
#define  STATUS_ABORTED_RUNTIME 138 
#define  STATUS_AUTOTUNE 137 
#define  STATUS_BYPASS 136 
#define  STATUS_CRACKED 135 
#define  STATUS_ERROR 134 
#define  STATUS_EXHAUSTED 133 
#define  STATUS_INIT 132 
#define  STATUS_PAUSED 131 
#define  STATUS_QUIT 130 
#define  STATUS_RUNNING 129 
#define  STATUS_SELFTEST 128 
 char const* ST_0000 ; 
 char const* ST_0001 ; 
 char const* ST_0002 ; 
 char const* ST_0003 ; 
 char const* ST_0004 ; 
 char const* ST_0005 ; 
 char const* ST_0006 ; 
 char const* ST_0007 ; 
 char const* ST_0008 ; 
 char const* ST_0009 ; 
 char const* ST_0010 ; 
 char const* ST_0011 ; 
 char const* ST_0012 ; 
 char const* ST_0013 ; 
 char const* ST_9999 ; 

const char *status_get_status_string (const hashcat_ctx_t *hashcat_ctx)
{
  const status_ctx_t *status_ctx = hashcat_ctx->status_ctx;

  const int devices_status = status_ctx->devices_status;

  // special case: running but checkpoint quit requested

  if (devices_status == STATUS_RUNNING)
  {
    if (status_ctx->checkpoint_shutdown == true)
    {
      return ST_0012;
    }
  }

  switch (devices_status)
  {
    case STATUS_INIT:               return ST_0000;
    case STATUS_AUTOTUNE:           return ST_0001;
    case STATUS_SELFTEST:           return ST_0002;
    case STATUS_RUNNING:            return ST_0003;
    case STATUS_PAUSED:             return ST_0004;
    case STATUS_EXHAUSTED:          return ST_0005;
    case STATUS_CRACKED:            return ST_0006;
    case STATUS_ABORTED:            return ST_0007;
    case STATUS_QUIT:               return ST_0008;
    case STATUS_BYPASS:             return ST_0009;
    case STATUS_ABORTED_CHECKPOINT: return ST_0010;
    case STATUS_ABORTED_RUNTIME:    return ST_0011;
    case STATUS_ERROR:              return ST_0013;
  }

  return ST_9999;
}
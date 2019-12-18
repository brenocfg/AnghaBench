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
typedef  int td_err_e ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  TD_BADKEY 148 
#define  TD_BADPH 147 
#define  TD_BADSH 146 
#define  TD_BADTA 145 
#define  TD_BADTH 144 
#define  TD_DBERR 143 
#define  TD_ERR 142 
#define  TD_MALLOC 141 
#define  TD_NOAPLIC 140 
#define  TD_NOCAPAB 139 
#define  TD_NOEVENT 138 
#define  TD_NOFPREGS 137 
#define  TD_NOLIBTHREAD 136 
#define  TD_NOLWP 135 
#define  TD_NOMSG 134 
#define  TD_NOSV 133 
#define  TD_NOTHR 132 
#define  TD_NOTSD 131 
#define  TD_NOXREGS 130 
#define  TD_OK 129 
#define  TD_PARTIALREG 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static char *
thread_db_err_str (td_err_e err)
{
  static char buf[64];

  switch (err)
    {
    case TD_OK:
      return "generic 'call succeeded'";
    case TD_ERR:
      return "generic error";
    case TD_NOTHR:
      return "no thread to satisfy query";
    case TD_NOSV:
      return "no sync handle to satisfy query";
    case TD_NOLWP:
      return "no LWP to satisfy query";
    case TD_BADPH:
      return "invalid process handle";
    case TD_BADTH:
      return "invalid thread handle";
    case TD_BADSH:
      return "invalid synchronization handle";
    case TD_BADTA:
      return "invalid thread agent";
    case TD_BADKEY:
      return "invalid key";
    case TD_NOMSG:
      return "no event message for getmsg";
    case TD_NOFPREGS:
      return "FPU register set not available";
    case TD_NOLIBTHREAD:
      return "application not linked with libthread";
    case TD_NOEVENT:
      return "requested event is not supported";
    case TD_NOCAPAB:
      return "capability not available";
    case TD_DBERR:
      return "debugger service failed";
    case TD_NOAPLIC:
      return "operation not applicable to";
    case TD_NOTSD:
      return "no thread-specific data for this thread";
    case TD_MALLOC:
      return "malloc failed";
    case TD_PARTIALREG:
      return "only part of register set was written/read";
    case TD_NOXREGS:
      return "X register set not available for this thread";
    default:
      snprintf (buf, sizeof (buf), "unknown thread_db error '%d'", err);
      return buf;
    }
}
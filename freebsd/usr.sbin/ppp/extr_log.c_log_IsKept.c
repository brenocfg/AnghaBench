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

/* Variables and functions */
 int LOG_KEPT_LOCAL ; 
 int LOG_KEPT_SYSLOG ; 
 int LogLOG ; 
 int LogMAX ; 
 int LogMAXCONF ; 
 int LogMIN ; 
 int LogMask ; 
 int LogMaskLocal ; 
 int MSK (int) ; 

int
log_IsKept(int id)
{
  if (id == LogLOG)
    return LOG_KEPT_SYSLOG;
  if (id < LogMIN || id > LogMAX)
    return 0;
  if (id > LogMAXCONF)
    return LOG_KEPT_LOCAL | LOG_KEPT_SYSLOG;

  return ((LogMaskLocal & MSK(id)) ? LOG_KEPT_LOCAL : 0) |
    ((LogMask & MSK(id)) ? LOG_KEPT_SYSLOG : 0);
}
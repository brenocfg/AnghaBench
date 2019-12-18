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
 int LOG_ALERT ; 
 int LOG_DEBUG ; 
 int LOG_ERR ; 
 int LOG_INFO ; 
 int LOG_WARNING ; 
#define  LogALERT 133 
#define  LogDEBUG 132 
#define  LogERROR 131 
#define  LogLOG 130 
 int LogMAX ; 
 int LogMIN ; 
#define  LogTIMER 129 
#define  LogWARN 128 

__attribute__((used)) static int
syslogLevel(int lev)
{
  switch (lev) {
  case LogLOG:
    return LOG_INFO;
  case LogDEBUG:
  case LogTIMER:
    return LOG_DEBUG;
  case LogWARN:
    return LOG_WARNING;
  case LogERROR:
    return LOG_ERR;
  case LogALERT:
    return LOG_ALERT;
  }
  return lev >= LogMIN && lev <= LogMAX ? LOG_INFO : 0;
}
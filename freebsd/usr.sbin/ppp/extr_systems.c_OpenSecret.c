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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * ID0fopen (char*,char*) ; 
 int /*<<< orphan*/  LogWARN ; 
 char* PPP_CONFDIR ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 

FILE *
OpenSecret(const char *file)
{
  FILE *fp;
  char line[100];

  snprintf(line, sizeof line, "%s/%s", PPP_CONFDIR, file);
  fp = ID0fopen(line, "r");
  if (fp == NULL)
    log_Printf(LogWARN, "OpenSecret: Can't open %s.\n", line);
  return (fp);
}
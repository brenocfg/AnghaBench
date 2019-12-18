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
 scalar_t__ issep (char) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
strip(char *line)
{
  int len;

  len = strlen(line);
  while (len && (line[len-1] == '\n' || line[len-1] == '\r' ||
                 issep(line[len-1])))
    line[--len] = '\0';

  while (issep(*line))
    line++;

  if (*line == '#')
    *line = '\0';

  return line;
}
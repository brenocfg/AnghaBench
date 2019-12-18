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
 int COLORS ; 
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  FATAL (char*,int,int) ; 
 scalar_t__ errno ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static int
extract_color (char *color)
{
  char *sEnd;
  int col = 0;

  if (strncasecmp (color, "color", 5) != 0)
    return -2;

  color += 5;
  col = strtol (color, &sEnd, 10);
  if (color == sEnd || *sEnd != '\0' || errno == ERANGE)
    return -2;
  /* ensure used color is supported by the terminal */
  if (col > COLORS)
    FATAL ("Terminal doesn't support color: %d - max colors: %d", col, COLORS);

  return col;
}
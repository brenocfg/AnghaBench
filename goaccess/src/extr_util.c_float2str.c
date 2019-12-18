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
 scalar_t__ snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,float) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,float) ; 
 char* xmalloc (scalar_t__) ; 

char *
float2str (float d, int width)
{
  char *s = xmalloc (snprintf (NULL, 0, "%*.2f", width, d) + 1);
  sprintf (s, "%*.2f", width, d);

  return s;
}
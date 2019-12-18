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
typedef  int u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

const char *
vj2asc(u_int32_t val)
{
  static char asc[50];		/* The return value is used immediately */

  if (val)
    snprintf(asc, sizeof asc, "%d VJ slots with%s slot compression",
            (int)((val>>8)&15)+1, val & 1 ?  "" : "out");
  else
    strcpy(asc, "VJ disabled");
  return asc;
}
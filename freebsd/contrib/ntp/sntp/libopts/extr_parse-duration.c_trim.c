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
 char NUL ; 
 scalar_t__ isspace (unsigned char) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
trim (char * pz)
{
  /* trim leading white space */
  while (isspace ((unsigned char)*pz))
    pz++;

  /* trim trailing white space */
  {
    char * pe = pz + strlen (pz);
    while ((pe > pz) && isspace ((unsigned char)pe[-1]))
      pe--;
    *pe = NUL;
  }

  return pz;
}
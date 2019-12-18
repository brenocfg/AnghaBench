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
 int _OPT_INT (char*) ; 
 scalar_t__ isalpha (unsigned char) ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static __inline  int
_OPT_BOOL(char *w)
{
     if(isalpha((unsigned char)*w))
	  return strcasecmp(w, "TRUE") == 0;
     else
	  return _OPT_INT(w);
}
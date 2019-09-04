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
 int ONIG_OPTION_EXTEND ; 
 int ONIG_OPTION_IGNORECASE ; 
 int ONIG_OPTION_MULTILINE ; 

__attribute__((used)) static char *
option_to_str(char str[4], int options) {
  char *p = str;
  if (options & ONIG_OPTION_MULTILINE) *p++ = 'm';
  if (options & ONIG_OPTION_IGNORECASE) *p++ = 'i';
  if (options & ONIG_OPTION_EXTEND) *p++ = 'x';
  *p = 0;
  return str;
}
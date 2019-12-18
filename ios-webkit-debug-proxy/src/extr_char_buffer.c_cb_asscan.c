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
 scalar_t__ calloc (scalar_t__,int) ; 
 int cb_sscan (char*,size_t*,char const*) ; 
 scalar_t__ realloc (char*,size_t) ; 
 scalar_t__ strlen (char const*) ; 

int cb_asscan(char **ret, size_t *to_length, const char *buf) {
  if (!ret || !*ret || !to_length || !buf) {
    return -1;
  }
  *ret = (char *)calloc(strlen(buf) + 1, sizeof(char));
  int rval = cb_sscan(*ret, to_length, buf);
  if (*ret && to_length) {
    *ret = (char*)realloc(*ret, *to_length * sizeof(char));
  }
  return rval;
}
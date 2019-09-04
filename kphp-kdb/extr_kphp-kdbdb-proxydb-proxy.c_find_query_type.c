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
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int t_getlex (char*,char*) ; 
 char* t_skipspc (char*,char*) ; 

int find_query_type (char *ptr, char *end) {
  int clen;
  while (ptr < end) {
    ptr = t_skipspc (ptr, end);
    clen = t_getlex (ptr, end);
    if (clen <= 0) {
      return 0;
    }
    if ((*ptr >= 'A' && *ptr <= 'Z') || (*ptr >= 'a' && *ptr <= 'z')) {
      if (clen == 6) {
	if (!memcmp (ptr, "SELECT", 6)) {
	  return -1;
	} else if (!memcmp (ptr, "UPDATE", 6)) {
	  return 1;
	} else if (!memcmp (ptr, "INSERT", 6)) {
	  return 1;
	} else if (!memcmp (ptr, "DELETE", 6)) {
	  return 1;
	}
      }
      if (clen == 4 && !memcmp (ptr, "SHOW", 4)) {
	return -1;
      }
    }
    ptr += clen;
  }
  return 0;
}
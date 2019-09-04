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
typedef  scalar_t__ qtype ;

/* Variables and functions */
 int MAX_QNAME ; 
 scalar_t__ get_qtype (char*) ; 

int check_qname (char *qname, qtype tp) {
  int i = 0;

  if (qname == NULL) {
    return 0;
  }

  if (tp != get_qtype (qname)) {
    return 0;
  }

  while (i <= MAX_QNAME && qname[i]) {
    if (!('A' <= qname[i] && qname[i] <= 'Z') && !('a' <= qname[i] && qname[i] <= 'z') &&
        !('0' <= qname[i] && qname[i] <= '9') && !(qname[i] == '_')) {
      return 0;
    }

    i++;
  }

  return 0 < i && i <= MAX_QNAME;
}
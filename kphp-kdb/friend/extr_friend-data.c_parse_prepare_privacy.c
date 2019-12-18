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
 int improve_privacy (int) ; 
 int parse_privacy (char const*,int) ; 

int parse_prepare_privacy (const char *text, int len, int owner_id) {
  int L = parse_privacy (text, len);
  if (L < 0) {
    return L;
  }
  return improve_privacy (owner_id);
}
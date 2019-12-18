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
 int SM_FIRSTINT ; 
 int SM_HASH ; 
 int SM_HASHDOT ; 
 int SM_NONE ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int get_split_mode (char *str) {
  if (!strncmp (str, "hash", 5)) {
    return SM_HASH;
  } else if (!strncmp (str, "firstint", 9)) {
    return SM_FIRSTINT;
  } else if (!strncmp (str, "hashdot", 8)) {
    return SM_HASHDOT;
  }
  return SM_NONE;
}
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
 int TF_ADDRESSES ; 
 int TF_EDUCATION ; 
 int TF_GROUPSHORT ; 
 int TF_MATCHES ; 
 int TF_MEMEXTRA ; 
 int TF_MEMGROUPS ; 
 int TF_MEMLITE ; 
 int TF_MEMSHORT ; 
 int TF_MILITARY ; 
 int TF_NAMES ; 
 int TF_NONE ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int get_dump_format (char *str) {
  if (!strncmp (str, "memlite", 7) || !strncmp (str, "members_lite", 12)) {
    return TF_MEMLITE;
  }
  if (!strncmp (str, "education", 9)) {
    return TF_EDUCATION;
  }
  if (!strncmp (str, "memshort", 8) || !strncmp (str, "members_short", 13)) {
    return TF_MEMSHORT;
  }
  if (!strncmp (str, "memextra", 8) || !strncmp (str, "members_extra", 13)) {
    return TF_MEMEXTRA;
  }
  if (!strncmp (str, "addresses", 9)) {
    return TF_ADDRESSES;
  }
  if (!strncmp (str, "groupshort", 10) || !strncmp (str, "groups_short", 12)) {
    return TF_GROUPSHORT;
  }
  if (!strncmp (str, "memgroups", 9) || !strncmp (str, "member_groups", 13)) {
    return TF_MEMGROUPS;
  }
  if (!strncmp (str, "military", 8)) {
    return TF_MILITARY;
  }
  if (!strncmp (str, "names", 5)) {
    return TF_NAMES;
  }
  if (!strncmp (str, "matches", 7)) {
    return TF_MATCHES;
  }

  return TF_NONE;
}
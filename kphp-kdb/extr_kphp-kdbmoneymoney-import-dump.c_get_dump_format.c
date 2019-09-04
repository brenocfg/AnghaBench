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
 int TF_ACCOUNTS ; 
 int TF_ACCTYPES ; 
 int TF_NONE ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int get_dump_format (char *str) {
  if (!strncmp (str, "acctypes", 8)) {
    return TF_ACCTYPES;
  }
  if (!strncmp (str, "account_types", 13)) {
    return TF_ACCTYPES;
  }
  if (!strncmp (str, "accounts", 8)) {
    return TF_ACCOUNTS;
  }

  return TF_NONE;
}
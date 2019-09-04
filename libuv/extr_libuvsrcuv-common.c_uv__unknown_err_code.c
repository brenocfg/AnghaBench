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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 char* uv__strdup (char*) ; 

__attribute__((used)) static const char* uv__unknown_err_code(int err) {
  char buf[32];
  char* copy;

  snprintf(buf, sizeof(buf), "Unknown system error %d", err);
  copy = uv__strdup(buf);

  return copy != NULL ? copy : "Unknown system error";
}
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
 char* memchr (char const*,int /*<<< orphan*/ ,size_t) ; 

size_t strnlen(const char* str, size_t maxlen) {
  char* p = memchr(str, 0, maxlen);
  if (p == NULL)
    return maxlen;
  else
    return p - str;
}
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
 unsigned long long crc64 (char const*,int) ; 
 int strlen (char const*) ; 

unsigned long long word_crc64 (const char *str, int len) {
  if (len < 0) { 
    len = strlen (str); 
  }
  return crc64 (str, len);
}
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
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_FALSE ; 
 int /*<<< orphan*/  BROTLI_TRUE ; 

__attribute__((used)) static BROTLI_BOOL ParseInt(const char* s, int low, int high, int* result) {
  int value = 0;
  int i;
  for (i = 0; i < 5; ++i) {
    char c = s[i];
    if (c == 0) break;
    if (s[i] < '0' || s[i] > '9') return BROTLI_FALSE;
    value = (10 * value) + (c - '0');
  }
  if (i == 0) return BROTLI_FALSE;
  if (i > 1 && s[0] == '0') return BROTLI_FALSE;
  if (s[i] != 0) return BROTLI_FALSE;
  if (value < low || value > high) return BROTLI_FALSE;
  *result = value;
  return BROTLI_TRUE;
}
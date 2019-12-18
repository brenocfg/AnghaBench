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
typedef  scalar_t__ ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static size_t posrelat (ptrdiff_t pos, size_t len) {
  if (pos >= 0) return (size_t)pos;
  else if (0u - (size_t)pos > len) return 0;
  else return len - ((size_t)-pos) + 1;
}
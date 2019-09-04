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
 int /*<<< orphan*/  tl_store_string_data (char const*,int) ; 
 int /*<<< orphan*/  tl_store_string_len (int) ; 

__attribute__((used)) static inline int tl_store_string (const char *s, int len) {
  tl_store_string_len (len);
  tl_store_string_data (s, len);
  return 0;
}
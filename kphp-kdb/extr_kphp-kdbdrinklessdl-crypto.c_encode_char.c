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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

inline char encode_char (char c) {
  if ('A' <= c && c <= 'Z') {
    return (char)(c - 'A');
  }
  if ('a' <= c && c <= 'z') {
    return (char)(c - 'a' + 26);
  }
  if ('0' <= c && c <= '9') {
    return (char)(c - '0' + 26 + 26);
  }
  if (c == '_') {
    return (char)(10 + 26 + 26);
  }
  assert (0);
}
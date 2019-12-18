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
 char N ; 
 int /*<<< orphan*/  assert (int) ; 

inline char decode_char (char c) {
  assert (0 <= c && c < N);
  if (c < 26) {
    return (char)(c + 'A');
  }
  c = (char)(c - 26);
  if (c < 26) {
    return (char)(c + 'a');
  }
  c = (char)(c - 26);
  if (c < 10) {
    return (char)(c + '0');
  }
  return '_';
}
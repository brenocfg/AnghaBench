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
 int /*<<< orphan*/  add_count (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  eolbyte ; 
 char const* lastnl ; 
 char* memchr (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  totalnl ; 

__attribute__((used)) static void
nlscan (char const *lim)
{
  size_t newlines = 0;
  char const *beg;
  for (beg = lastnl; beg != lim; beg = memchr (beg, eolbyte, lim - beg), beg++)
    newlines++;
  totalnl = add_count (totalnl, newlines);
  lastnl = lim;
}
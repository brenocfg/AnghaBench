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

__attribute__((used)) static void
token_discard_all(void *baton)
{
  /* Do nothing.
     Note that in the file case, this function discards all
     tokens allocated, but we're geared toward small in-memory diffs.
     Meaning that there's no special pool to clear.
  */
}
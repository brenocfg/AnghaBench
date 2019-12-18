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
struct mallinfo {int dummy; } ;
typedef  int /*<<< orphan*/  mstate ;
typedef  int /*<<< orphan*/  mspace ;

/* Variables and functions */
 int /*<<< orphan*/  USAGE_ERROR_ACTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mallinfo internal_mallinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_magic (int /*<<< orphan*/ ) ; 

struct mallinfo mspace_mallinfo(mspace msp) {
  mstate ms = (mstate)msp;
  if (!ok_magic(ms)) {
    USAGE_ERROR_ACTION(ms,ms);
  }
  return internal_mallinfo(ms);
}
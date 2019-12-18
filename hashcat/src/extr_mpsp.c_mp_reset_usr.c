#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/  cs_buf; scalar_t__ cs_len; } ;
typedef  TYPE_1__ cs_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mp_reset_usr (cs_t *mp_usr, const u32 userindex)
{
  mp_usr[userindex].cs_len = 0;

  memset (mp_usr[userindex].cs_buf, 0, sizeof (mp_usr[userindex].cs_buf));
}
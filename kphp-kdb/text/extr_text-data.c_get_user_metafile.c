#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mf; } ;
typedef  TYPE_1__ user_t ;
struct TYPE_6__ {char* data; } ;
typedef  TYPE_2__ core_mf_t ;

/* Variables and functions */
 TYPE_2__* touch_metafile (int /*<<< orphan*/ ) ; 

inline char *get_user_metafile (user_t *U) {
  core_mf_t *M = touch_metafile (U->mf);
  return M ? M->data : 0;
}
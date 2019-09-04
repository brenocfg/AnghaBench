#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  st_mode; } ;
struct TYPE_5__ {TYPE_1__ st; } ;
typedef  TYPE_2__ file_t ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  directories ; 
 int /*<<< orphan*/  regulars ; 
 int /*<<< orphan*/  symlinks ; 

__attribute__((used)) static void incr_file_mode_stat (file_t *x) {
  if (S_ISLNK (x->st.st_mode)) {
    symlinks++;
  } else if (S_ISDIR (x->st.st_mode)) {
    directories++;
  } else {
    regulars++;
  }
}
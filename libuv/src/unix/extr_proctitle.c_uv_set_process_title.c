#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_process_title_mutex_once ; 
 TYPE_1__ process_title ; 
 int /*<<< orphan*/  process_title_mutex ; 
 int /*<<< orphan*/  process_title_mutex_once ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  uv__set_process_title (char const*) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int uv_set_process_title(const char* title) {
  uv_once(&process_title_mutex_once, init_process_title_mutex_once);
  uv_mutex_lock(&process_title_mutex);

  if (process_title.len != 0) {
    /* No need to terminate, byte after is always '\0'. */
    strncpy(process_title.str, title, process_title.len);
    uv__set_process_title(title);
  }

  uv_mutex_unlock(&process_title_mutex);

  return 0;
}
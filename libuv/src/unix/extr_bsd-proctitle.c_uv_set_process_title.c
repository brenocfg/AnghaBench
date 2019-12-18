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
 int UV_ENOMEM ; 
 int /*<<< orphan*/  init_process_title_mutex_once ; 
 char* process_title ; 
 int /*<<< orphan*/  process_title_mutex ; 
 int /*<<< orphan*/  process_title_mutex_once ; 
 int /*<<< orphan*/  setproctitle (char*,char const*) ; 
 int /*<<< orphan*/  uv__free (char*) ; 
 char* uv__strdup (char const*) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int uv_set_process_title(const char* title) {
  char* new_title;

  new_title = uv__strdup(title);
  if (new_title == NULL)
    return UV_ENOMEM;

  uv_once(&process_title_mutex_once, init_process_title_mutex_once);
  uv_mutex_lock(&process_title_mutex);

  uv__free(process_title);
  process_title = new_title;
  setproctitle("%s", title);

  uv_mutex_unlock(&process_title_mutex);

  return 0;
}
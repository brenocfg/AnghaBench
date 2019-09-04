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
 int process_argc ; 
 char** process_argv ; 
 int /*<<< orphan*/  process_title_mutex ; 
 int /*<<< orphan*/  process_title_mutex_once ; 
 char* process_title_ptr ; 
 int /*<<< orphan*/  uv__free (char*) ; 
 char* uv__strdup (char const*) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int uv_set_process_title(const char* title) {
  char* new_title;

  /* We cannot free this pointer when libuv shuts down,
   * the process may still be using it.
   */
  new_title = uv__strdup(title);
  if (new_title == NULL)
    return UV_ENOMEM;

  uv_once(&process_title_mutex_once, init_process_title_mutex_once);
  uv_mutex_lock(&process_title_mutex);

  /* If this is the first time this is set,
   * don't free and set argv[1] to NULL.
   */
  if (process_title_ptr != NULL)
    uv__free(process_title_ptr);

  process_title_ptr = new_title;

  process_argv[0] = process_title_ptr;
  if (process_argc > 1)
     process_argv[1] = NULL;

  uv_mutex_unlock(&process_title_mutex);

  return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_5__ {int /*<<< orphan*/ * stream; } ;
struct TYPE_6__ {int flags; TYPE_1__ data; } ;
typedef  TYPE_2__ uv_stdio_container_t ;
struct TYPE_7__ {char** args; int stdio_count; TYPE_2__* stdio; int /*<<< orphan*/  exit_cb; void* file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int UV_CREATE_PIPE ; 
 int UV_IGNORE ; 
 int UV_WRITABLE_PIPE ; 
 char** args ; 
 void* exepath ; 
 int /*<<< orphan*/  exit_cb ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  on_alloc ; 
 int /*<<< orphan*/  on_read ; 
 TYPE_3__ options ; 
 int /*<<< orphan*/  out ; 
 scalar_t__ output_used ; 
 int pipe_open ; 
 int /*<<< orphan*/  process ; 
 int process_open ; 
 int /*<<< orphan*/  uv_pipe_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_spawn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void spawn(void) {
  uv_stdio_container_t stdio[2];
  int r;

  ASSERT(process_open == 0);
  ASSERT(pipe_open == 0);

  args[0] = exepath;
  args[1] = "spawn_helper";
  args[2] = NULL;
  options.file = exepath;
  options.args = args;
  options.exit_cb = exit_cb;

  uv_pipe_init(loop, &out, 0);

  options.stdio = stdio;
  options.stdio_count = 2;
  options.stdio[0].flags = UV_IGNORE;
  options.stdio[1].flags = UV_CREATE_PIPE | UV_WRITABLE_PIPE;
  options.stdio[1].data.stream = (uv_stream_t*)&out;

  r = uv_spawn(loop, &process, &options);
  ASSERT(r == 0);

  process_open = 1;
  pipe_open = 1;
  output_used = 0;

  r = uv_read_start((uv_stream_t*) &out, on_alloc, on_read);
  ASSERT(r == 0);
}
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
struct TYPE_4__ {int /*<<< orphan*/  stream; } ;
struct TYPE_5__ {int flags; TYPE_1__ data; } ;
typedef  TYPE_2__ uv_stdio_container_t ;

/* Variables and functions */
 int UV_CREATE_PIPE ; 
 int /*<<< orphan*/  uv__stream_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uv__process_close_stream(uv_stdio_container_t* container) {
  if (!(container->flags & UV_CREATE_PIPE)) return;
  uv__stream_close(container->data.stream);
}
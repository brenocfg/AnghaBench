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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ uv_handle_t ;

/* Variables and functions */
 int UV_HANDLE_ACTIVE ; 
 int UV_HANDLE_CLOSING ; 

int uv_is_active(const uv_handle_t* handle) {
  return (handle->flags & UV_HANDLE_ACTIVE) &&
        !(handle->flags & UV_HANDLE_CLOSING);
}
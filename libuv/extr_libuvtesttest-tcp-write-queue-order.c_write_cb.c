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
typedef  int /*<<< orphan*/  uv_write_t ;

/* Variables and functions */
 int UV_ECANCELED ; 
 int /*<<< orphan*/  write_callbacks ; 
 int /*<<< orphan*/  write_cancelled_callbacks ; 
 int /*<<< orphan*/  write_error_callbacks ; 

__attribute__((used)) static void write_cb(uv_write_t* req, int status) {
  if (status == 0)
    write_callbacks++;
  else if (status == UV_ECANCELED)
    write_cancelled_callbacks++;
  else
    write_error_callbacks++;
}
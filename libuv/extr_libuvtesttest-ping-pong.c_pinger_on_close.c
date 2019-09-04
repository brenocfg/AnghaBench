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
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_1__ uv_handle_t ;
struct TYPE_6__ {scalar_t__ pongs; } ;
typedef  TYPE_2__ pinger_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ NUM_PINGS ; 
 int /*<<< orphan*/  completed_pingers ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void pinger_on_close(uv_handle_t* handle) {
  pinger_t* pinger = (pinger_t*)handle->data;

  ASSERT(NUM_PINGS == pinger->pongs);

  free(pinger);

  completed_pingers++;
}
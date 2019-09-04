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
struct TYPE_5__ {scalar_t__ base; } ;
typedef  TYPE_1__ uv_buf_t ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ buf_t ;

/* Variables and functions */
 TYPE_2__* buf_freelist ; 

__attribute__((used)) static void buf_free(const uv_buf_t* buf) {
  buf_t* ab = (buf_t*) buf->base - 1;
  ab->next = buf_freelist;
  buf_freelist = ab;
}
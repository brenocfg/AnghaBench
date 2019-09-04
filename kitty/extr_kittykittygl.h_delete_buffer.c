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
typedef  size_t ssize_t ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ id; } ;

/* Variables and functions */
 TYPE_1__* buffers ; 
 int /*<<< orphan*/  glDeleteBuffers (int,scalar_t__*) ; 

__attribute__((used)) static void
delete_buffer(ssize_t buf_idx) {
    glDeleteBuffers(1, &(buffers[buf_idx].id));
    buffers[buf_idx].id = 0;
    buffers[buf_idx].size = 0;
}
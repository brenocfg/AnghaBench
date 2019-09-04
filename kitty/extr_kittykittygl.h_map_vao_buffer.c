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
struct TYPE_2__ {size_t* buffers; } ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  bind_buffer (size_t) ; 
 void* map_buffer (size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* vaos ; 

__attribute__((used)) static void*
map_vao_buffer(ssize_t vao_idx, size_t bufnum, GLenum access) {
    ssize_t buf_idx = vaos[vao_idx].buffers[bufnum];
    bind_buffer(buf_idx);
    return map_buffer(buf_idx, access);
}
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
typedef  int /*<<< orphan*/  GLsizeiptr ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_buffer (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_buffer (size_t) ; 
 TYPE_1__* vaos ; 

__attribute__((used)) static ssize_t
alloc_vao_buffer(ssize_t vao_idx, GLsizeiptr size, size_t bufnum, GLenum usage) {
    ssize_t buf_idx = vaos[vao_idx].buffers[bufnum];
    bind_buffer(buf_idx);
    alloc_buffer(buf_idx, size, usage);
    return buf_idx;
}
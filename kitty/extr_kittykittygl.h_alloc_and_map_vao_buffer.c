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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  GLsizeiptr ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_vao_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 void* map_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void*
alloc_and_map_vao_buffer(ssize_t vao_idx, GLsizeiptr size, size_t bufnum, GLenum usage, GLenum access) {
    ssize_t buf_idx = alloc_vao_buffer(vao_idx, size, bufnum, usage);
    return map_buffer(buf_idx, access);
}
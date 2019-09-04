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
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  usage; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  GLsizeiptr ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  TYPE_1__ Buffer ;

/* Variables and functions */
 TYPE_1__* buffers ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
alloc_buffer(ssize_t idx, GLsizeiptr size, GLenum usage) {
    Buffer *b = buffers + idx;
    if (b->size == size) return;
    b->size = size;
    glBufferData(b->usage, size, NULL, usage);
}
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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  glBindVertexArray (int /*<<< orphan*/ ) ; 
 TYPE_1__* vaos ; 

__attribute__((used)) static void
bind_vertex_array(ssize_t vao_idx) {
    glBindVertexArray(vaos[vao_idx].id);
}
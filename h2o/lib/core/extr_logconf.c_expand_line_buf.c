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

/* Variables and functions */
 char* h2o_mem_alloc (size_t) ; 
 char* h2o_mem_realloc (char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

__attribute__((used)) static char *expand_line_buf(char *line, size_t *cur_size, size_t required, int should_realloc)
{
    size_t new_size = *cur_size;

    /* determine the new size */
    do {
        new_size *= 2;
    } while (new_size < required);

    /* reallocate */
    if (!should_realloc) {
        char *newpt = h2o_mem_alloc(new_size);
        memcpy(newpt, line, *cur_size);
        line = newpt;
    } else {
        line = h2o_mem_realloc(line, new_size);
    }
    *cur_size = new_size;

    return line;
}
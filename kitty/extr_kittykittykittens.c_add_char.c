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
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 size_t CMD_BUF_SZ ; 
 int /*<<< orphan*/  append_buf (char*,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
add_char(char buf[CMD_BUF_SZ], size_t *pos, char ch, PyObject *ans) {
    if (*pos >= CMD_BUF_SZ) {
        if (!append_buf(buf, pos, ans)) return false;
    }
    buf[*pos] = ch;
    *pos += 1;
    return true;
}
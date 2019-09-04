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
typedef  int /*<<< orphan*/  LineBuf ;

/* Variables and functions */
 int /*<<< orphan*/  LineBuf_Type ; 
 int /*<<< orphan*/  Py_BuildValue (char*,unsigned int,unsigned int) ; 
 scalar_t__ new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

LineBuf *alloc_linebuf(unsigned int lines, unsigned int columns) {
    return (LineBuf*)new(&LineBuf_Type, Py_BuildValue("II", lines, columns), NULL);
}
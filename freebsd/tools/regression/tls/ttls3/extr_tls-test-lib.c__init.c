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
 int /*<<< orphan*/  __GL_TLS_SET (int,void*) ; 
 int /*<<< orphan*/  __gl_tls_init_offsets () ; 

void _init(void)
{
    __gl_tls_init_offsets();

    __GL_TLS_SET(0, (void *) 0xff000000);
    __GL_TLS_SET(1, (void *) 0xff000001);
    __GL_TLS_SET(2, (void *) 0xff000002);
    __GL_TLS_SET(3, (void *) 0xff000003);
    __GL_TLS_SET(4, (void *) 0xff000004);
    __GL_TLS_SET(5, (void *) 0xff000005);
    __GL_TLS_SET(6, (void *) 0xff000006);
    __GL_TLS_SET(7, (void *) 0xff000007);
}
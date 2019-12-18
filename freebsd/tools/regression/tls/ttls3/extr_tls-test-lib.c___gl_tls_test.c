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
 int /*<<< orphan*/  __GL_TLS_GET (int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

void __gl_tls_test(void)
{
    printf("__GL_TLS_GET(0) = %p\n", __GL_TLS_GET(0));
    printf("__GL_TLS_GET(1) = %p\n", __GL_TLS_GET(1));
    printf("__GL_TLS_GET(2) = %p\n", __GL_TLS_GET(2));
    printf("__GL_TLS_GET(3) = %p\n", __GL_TLS_GET(3));
    printf("__GL_TLS_GET(4) = %p\n", __GL_TLS_GET(4));
    printf("__GL_TLS_GET(5) = %p\n", __GL_TLS_GET(5));
    printf("__GL_TLS_GET(6) = %p\n", __GL_TLS_GET(6));
    printf("__GL_TLS_GET(7) = %p\n", __GL_TLS_GET(7));
}
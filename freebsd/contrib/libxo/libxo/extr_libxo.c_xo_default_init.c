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
typedef  int /*<<< orphan*/  xo_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  XOF_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_NO_ENV ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  xo_default_handle ; 
 int xo_default_inited ; 
 int /*<<< orphan*/  xo_init_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xo_set_options_simple (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
xo_default_init (void)
{
    xo_handle_t *xop = &xo_default_handle;

    xo_init_handle(xop);

#if !defined(NO_LIBXO_OPTIONS)
    if (!XOF_ISSET(xop, XOF_NO_ENV)) {
       char *env = getenv("LIBXO_OPTIONS");

       if (env)
           xo_set_options_simple(xop, env);

    }
#endif /* NO_LIBXO_OPTIONS */

    xo_default_inited = 1;
}
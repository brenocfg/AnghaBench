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
struct TYPE_2__ {int (* add_cb ) (int /*<<< orphan*/ *,unsigned int,unsigned char const**,size_t*,int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  add_arg; } ;
typedef  TYPE_1__ custom_ext_add_cb_wrap ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,unsigned int,unsigned char const**,size_t*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int custom_ext_add_old_cb_wrap(SSL *s, unsigned int ext_type,
                                      unsigned int context,
                                      const unsigned char **out,
                                      size_t *outlen, X509 *x, size_t chainidx,
                                      int *al, void *add_arg)
{
    custom_ext_add_cb_wrap *add_cb_wrap = (custom_ext_add_cb_wrap *)add_arg;

    if (add_cb_wrap->add_cb == NULL)
        return 1;

    return add_cb_wrap->add_cb(s, ext_type, out, outlen, al,
                               add_cb_wrap->add_arg);
}
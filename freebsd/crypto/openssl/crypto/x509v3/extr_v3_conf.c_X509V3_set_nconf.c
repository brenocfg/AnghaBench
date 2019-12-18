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
struct TYPE_3__ {int /*<<< orphan*/ * db; int /*<<< orphan*/ * db_meth; } ;
typedef  TYPE_1__ X509V3_CTX ;
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  nconf_method ; 

void X509V3_set_nconf(X509V3_CTX *ctx, CONF *conf)
{
    ctx->db_meth = &nconf_method;
    ctx->db = conf;
}
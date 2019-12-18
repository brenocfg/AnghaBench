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
typedef  void* krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_LOCALEDIR ; 
 int /*<<< orphan*/  HEIMDAL_TEXTDOMAIN ; 
 int /*<<< orphan*/  _krb5_load_plugins (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysplugin_dirs ; 

__attribute__((used)) static void
init_context_once(void *ctx)
{
    krb5_context context = ctx;

    _krb5_load_plugins(context, "krb5", sysplugin_dirs);

    bindtextdomain(HEIMDAL_TEXTDOMAIN, HEIMDAL_LOCALEDIR);
}
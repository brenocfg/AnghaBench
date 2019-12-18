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
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/ * announce_config ; 
 int /*<<< orphan*/  announce_context ; 
 int /*<<< orphan*/  create_dns_sd () ; 
 int /*<<< orphan*/  dispatch_queue_create (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  g_queue ; 
 int /*<<< orphan*/  g_store ; 
 int /*<<< orphan*/  register_notification () ; 

void
bonjour_announce(krb5_context context, krb5_kdc_configuration *config)
{
#if defined(__APPLE__) && defined(HAVE_GCD)
    g_queue = dispatch_queue_create("com.apple.kdc_announce", NULL);
    if (!g_queue)
	errx(1, "dispatch_queue_create");

    g_store = register_notification();
    announce_config = config;
    announce_context = context;

    create_dns_sd();
#endif
}
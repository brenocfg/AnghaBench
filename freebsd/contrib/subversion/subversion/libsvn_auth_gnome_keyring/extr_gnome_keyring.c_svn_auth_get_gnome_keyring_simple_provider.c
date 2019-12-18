#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ svn_auth_provider_object_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gnome_keyring_simple_provider ; 
 int /*<<< orphan*/  init_gnome_keyring () ; 

void
svn_auth_get_gnome_keyring_simple_provider
    (svn_auth_provider_object_t **provider,
     apr_pool_t *pool)
{
  svn_auth_provider_object_t *po = apr_pcalloc(pool, sizeof(*po));

  po->vtable = &gnome_keyring_simple_provider;
  *provider = po;

#ifdef SVN_HAVE_GNOME_KEYRING
  init_gnome_keyring();
#endif
}
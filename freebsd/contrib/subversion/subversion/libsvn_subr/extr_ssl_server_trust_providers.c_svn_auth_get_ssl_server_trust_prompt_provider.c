#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_auth_ssl_server_trust_prompt_func_t ;
struct TYPE_6__ {TYPE_2__* provider_baton; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ svn_auth_provider_object_t ;
struct TYPE_7__ {void* prompt_baton; int /*<<< orphan*/  prompt_func; } ;
typedef  TYPE_2__ ssl_server_trust_prompt_provider_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_2__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ssl_server_trust_prompt_provider ; 

void
svn_auth_get_ssl_server_trust_prompt_provider
  (svn_auth_provider_object_t **provider,
   svn_auth_ssl_server_trust_prompt_func_t prompt_func,
   void *prompt_baton,
   apr_pool_t *pool)
{
  svn_auth_provider_object_t *po = apr_pcalloc(pool, sizeof(*po));
  ssl_server_trust_prompt_provider_baton_t *pb =
    apr_palloc(pool, sizeof(*pb));
  pb->prompt_func = prompt_func;
  pb->prompt_baton = prompt_baton;
  po->vtable = &ssl_server_trust_prompt_provider;
  po->provider_baton = pb;
  *provider = po;
}
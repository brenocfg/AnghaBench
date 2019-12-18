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
struct TYPE_3__ {scalar_t__ parameters; scalar_t__ slave_parameters; } ;
typedef  TYPE_1__ svn_auth_baton_t ;

/* Variables and functions */
 int /*<<< orphan*/  auth_NULL ; 
 int /*<<< orphan*/  svn_hash_sets (scalar_t__,char const*,void const*) ; 

void
svn_auth_set_parameter(svn_auth_baton_t *auth_baton,
                       const char *name,
                       const void *value)
{
  if (auth_baton)
    {
      if (auth_baton->slave_parameters)
        {
          if (!value)
            value = &auth_NULL;

          svn_hash_sets(auth_baton->slave_parameters, name, value);
        }
      else
        svn_hash_sets(auth_baton->parameters, name, value);
    }
}
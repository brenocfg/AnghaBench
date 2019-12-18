#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
struct TYPE_6__ {int /*<<< orphan*/ * last_token; int /*<<< orphan*/  tokens; } ;
typedef  TYPE_2__ ra_svn_driver_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_token(ra_svn_driver_state_t *ds,
                         svn_string_t *token)
{
  apr_hash_set(ds->tokens, token->data, token->len, NULL);

  /* Reset this unconditionally.  In most cases, LAST_TOKEN->TOKEN will
     match TOKEN anyway and if it doesn't, lookup_token() will suffer only
     a minor performance hit. */
  ds->last_token = NULL;
}
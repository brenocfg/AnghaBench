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
struct notify_baton {int /*<<< orphan*/  conflicted_paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_HASH_KEY_STRING ; 
 int /*<<< orphan*/  apr_hash_pool_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
add_conflicted_path(struct notify_baton *nb, const char *path)
{
  apr_hash_set(nb->conflicted_paths,
               apr_pstrdup(apr_hash_pool_get(nb->conflicted_paths), path),
               APR_HASH_KEY_STRING, "");
}
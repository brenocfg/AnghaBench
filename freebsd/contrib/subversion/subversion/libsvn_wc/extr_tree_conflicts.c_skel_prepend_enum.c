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
typedef  int /*<<< orphan*/  svn_token_map_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_skel__prepend (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__str_atom (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_token__to_word (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void
skel_prepend_enum(svn_skel_t *skel,
                  const svn_token_map_t *map,
                  int n,
                  apr_pool_t *result_pool)
{
  svn_skel__prepend(svn_skel__str_atom(svn_token__to_word(map, n),
                                       result_pool), skel);
}
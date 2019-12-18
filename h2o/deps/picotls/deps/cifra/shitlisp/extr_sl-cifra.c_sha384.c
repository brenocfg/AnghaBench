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
typedef  int /*<<< orphan*/  sl_value ;
typedef  int /*<<< orphan*/  sl_symboltab ;

/* Variables and functions */
 int /*<<< orphan*/  cf_sha384 ; 
 int /*<<< orphan*/ * hash_fn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static sl_value * sha384(sl_value *self, sl_value *args, sl_symboltab *tab)
{
  return hash_fn(self, args, tab, &cf_sha384);
}
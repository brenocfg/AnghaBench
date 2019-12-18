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
typedef  int /*<<< orphan*/  uint32_t ;
struct table_val_link {int /*<<< orphan*/  pval; } ;
struct named_object {int dummy; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static int
cmp_table_value(struct named_object *no, const void *key, uint32_t kopt)
{

	return (memcmp(((struct table_val_link *)no)->pval, key, 56));
}
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
typedef  int /*<<< orphan*/  GModule ;

/* Variables and functions */
 int /*<<< orphan*/  ht_insert_hits (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ht_insert_meta_data (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
insert_hit (int data_nkey, GModule module)
{
  ht_insert_hits (module, data_nkey, 1);
  ht_insert_meta_data (module, "hits", 1);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int len; int /*<<< orphan*/  vec; } ;
typedef  TYPE_1__ prof_bt_t ;

/* Variables and functions */
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  hash (int /*<<< orphan*/ ,int,int,size_t*) ; 

__attribute__((used)) static void
prof_bt_hash(const void *key, size_t r_hash[2]) {
	prof_bt_t *bt = (prof_bt_t *)key;

	cassert(config_prof);

	hash(bt->vec, bt->len * sizeof(void *), 0x94122f33U, r_hash);
}
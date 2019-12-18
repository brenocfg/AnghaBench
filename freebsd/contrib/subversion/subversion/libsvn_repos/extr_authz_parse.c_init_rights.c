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
struct TYPE_3__ {int /*<<< orphan*/  max_access; int /*<<< orphan*/  min_access; } ;
typedef  TYPE_1__ authz_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  authz_access_none ; 
 int /*<<< orphan*/  authz_access_write ; 

__attribute__((used)) static void init_rights(authz_rights_t *rights)
{
  rights->min_access = authz_access_write;
  rights->max_access = authz_access_none;
 }
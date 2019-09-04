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
struct rpc_schema {scalar_t__ num; } ;

/* Variables and functions */
 scalar_t__ MAX_SCHEMAS ; 
 int /*<<< orphan*/  assert (int) ; 
 struct rpc_schema** schemas ; 
 scalar_t__ schemas_num ; 

void rpc_schema_add (struct rpc_schema *E) {
  assert (schemas_num < MAX_SCHEMAS);
  E->num = schemas_num;
  schemas[schemas_num ++] = E;
}
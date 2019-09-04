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
struct rpc_extension {scalar_t__ num; } ;

/* Variables and functions */
 scalar_t__ MAX_EXTENSIONS ; 
 int /*<<< orphan*/  assert (int) ; 
 struct rpc_extension** extensions ; 
 scalar_t__ extensions_num ; 

void rpc_extension_add (struct rpc_extension *E) {
  assert (extensions_num < MAX_EXTENSIONS);
  E->num = extensions_num;
  extensions[extensions_num ++] = E;
}
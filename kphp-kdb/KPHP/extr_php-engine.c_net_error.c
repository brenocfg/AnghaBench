#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ans; } ;
typedef  TYPE_2__ php_query_base_t ;
struct TYPE_10__ {TYPE_1__* func; int /*<<< orphan*/  ans; } ;
typedef  TYPE_3__ net_ansgen_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* free ) (TYPE_3__*) ;int /*<<< orphan*/  (* error ) (TYPE_3__*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  php_script ; 
 int /*<<< orphan*/  php_script_query_answered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

void net_error (net_ansgen_t *ansgen, php_query_base_t *query, const char *err) {
  ansgen->func->error (ansgen, err);
  query->ans = ansgen->ans;
  ansgen->func->free (ansgen);
  php_script_query_answered (php_script);
}
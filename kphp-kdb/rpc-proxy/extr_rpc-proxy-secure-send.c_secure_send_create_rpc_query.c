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
struct rpc_query {int dummy; } ;

/* Variables and functions */
 struct rpc_query* _secure_send_create_rpc_query (long long,int /*<<< orphan*/ ) ; 

struct rpc_query *secure_send_create_rpc_query (long long new_qid) {
  return _secure_send_create_rpc_query (new_qid, 0);
}
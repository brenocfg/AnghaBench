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
struct rpc_get_file_data {int fwd_header_ints; struct rpc_get_file_data* fwd_header; TYPE_1__* meta; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfree (struct rpc_get_file_data*,int) ; 

__attribute__((used)) static void rpc_get_file_data_free (struct rpc_get_file_data *L) {
  if (L->meta) {
    L->meta->refcnt--;
  }
  if (L->fwd_header) {
    zfree (L->fwd_header, 4 * L->fwd_header_ints);
  }
  zfree (L, sizeof (struct rpc_get_file_data));
}
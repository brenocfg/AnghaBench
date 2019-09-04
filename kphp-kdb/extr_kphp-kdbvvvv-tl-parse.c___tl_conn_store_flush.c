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
struct TYPE_2__ {int /*<<< orphan*/  (* flush_packet ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* RPCS_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TL_OUT_CONN ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __tl_conn_store_flush (void) {
  RPCS_FUNC(TL_OUT_CONN)->flush_packet(TL_OUT_CONN);
}
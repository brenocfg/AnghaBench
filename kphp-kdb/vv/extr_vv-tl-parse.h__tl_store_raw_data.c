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
struct TYPE_2__ {int /*<<< orphan*/  (* store_raw_data ) (void const*,int) ;} ;

/* Variables and functions */
 TYPE_1__* TL_OUT_METHODS ; 
 int TL_OUT_POS ; 
 int TL_OUT_REMAINING ; 
 int /*<<< orphan*/  stub1 (void const*,int) ; 

__attribute__((used)) static inline void _tl_store_raw_data (const void *buf, int len) {
  TL_OUT_METHODS->store_raw_data (buf, len);
  TL_OUT_POS += len;
  TL_OUT_REMAINING -= len;
}
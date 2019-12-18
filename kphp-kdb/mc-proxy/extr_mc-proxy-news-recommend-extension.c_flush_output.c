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
struct connection {int dummy; } ;
struct TYPE_2__ {int (* flush_query ) (struct connection*) ;} ;

/* Variables and functions */
 TYPE_1__* MCC_FUNC (struct connection*) ; 
 int stub1 (struct connection*) ; 

__attribute__((used)) static inline int flush_output (struct connection *c) {
  return MCC_FUNC (c)->flush_query (c);
}
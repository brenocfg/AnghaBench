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
struct tl_saved_query {scalar_t__ extra; } ;
struct saved_data_auto {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfree (scalar_t__,int) ; 

__attribute__((used)) static inline void tl_saved_query_free_auto (struct tl_saved_query *q) {
  if (*(int *)(q->extra) > 0) { return; };
  zfree (q->extra, sizeof (struct saved_data_auto));
}
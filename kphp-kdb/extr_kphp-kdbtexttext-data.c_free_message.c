#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ len; } ;
typedef  TYPE_1__ message_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  incore_messages ; 
 scalar_t__ text_shift ; 
 int /*<<< orphan*/  zfree (TYPE_1__*,scalar_t__) ; 

inline void free_message (message_t *M) {
  assert (M);
  zfree (M, M->len + sizeof (message_t) + text_shift);
  incore_messages--;
}
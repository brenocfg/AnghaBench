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
struct connection {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int write_out (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static void __m_to_conn (void *_c, const void *data, int len) {
  struct connection *c = (struct connection *)_c;
  assert (write_out (&c->Out, data, len) == len);
}
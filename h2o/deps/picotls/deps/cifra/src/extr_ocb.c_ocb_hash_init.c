#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int i; int /*<<< orphan*/  sum; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ ocb_hash ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ocb_hash_init(ocb_hash *h)
{
  memset(h->offset, 0, sizeof h->offset);
  memset(h->sum, 0, sizeof h->sum);
  h->i = 1;
}
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
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  fp; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ out_t ;

/* Variables and functions */
 int /*<<< orphan*/  hc_fwrite (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void out_flush (out_t *out)
{
  if (out->len == 0) return;

  hc_fwrite (out->buf, 1, out->len, &out->fp);

  out->len = 0;
}
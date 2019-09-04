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
typedef  int /*<<< orphan*/  h2o_iovec_t ;
struct TYPE_2__ {int /*<<< orphan*/  const buf; } ;

/* Variables and functions */
 int H2O_MAX_TOKENS ; 
 TYPE_1__* h2o__tokens ; 

int h2o_iovec_is_token(const h2o_iovec_t *buf)
{
    return &h2o__tokens[0].buf <= buf && buf <= &h2o__tokens[H2O_MAX_TOKENS - 1].buf;
}
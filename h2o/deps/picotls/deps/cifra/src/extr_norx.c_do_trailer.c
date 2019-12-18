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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  norx32_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_TRAILER ; 
 int /*<<< orphan*/  input (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  switch_domain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_trailer(norx32_ctx *ctx, const uint8_t *buf, size_t nbuf)
{
  if (nbuf)
  {
    switch_domain(ctx, DOMAIN_TRAILER);
    input(ctx, DOMAIN_TRAILER, buf, nbuf);
  }
}
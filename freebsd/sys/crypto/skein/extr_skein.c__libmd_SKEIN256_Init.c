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
typedef  int /*<<< orphan*/  SKEIN256_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  Skein_256_Init (int /*<<< orphan*/ *,int) ; 

void
SKEIN256_Init(SKEIN256_CTX * ctx)
{

	Skein_256_Init(ctx, 256);
}
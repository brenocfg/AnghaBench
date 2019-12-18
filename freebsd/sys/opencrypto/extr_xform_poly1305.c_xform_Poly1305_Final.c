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

/* Variables and functions */
 int /*<<< orphan*/  Poly1305_Final (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
xform_Poly1305_Final(uint8_t *digest, void *ctx)
{
	Poly1305_Final(digest, ctx);
}
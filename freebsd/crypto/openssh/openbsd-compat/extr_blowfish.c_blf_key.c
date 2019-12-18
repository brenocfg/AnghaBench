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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  blf_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  Blowfish_expand0state (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Blowfish_initstate (int /*<<< orphan*/ *) ; 

void
blf_key(blf_ctx *c, const u_int8_t *k, u_int16_t len)
{
	/* Initialize S-boxes and subkeys with Pi */
	Blowfish_initstate(c);

	/* Transform S-boxes and subkeys with key */
	Blowfish_expand0state(c, k, len);
}